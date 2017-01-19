/* Minimal example program that demonstrates how to use libsndfile-MSVC */
/* The code in this file (only in this file!) is dedicated to the public domain, by LoRd_MuldeR <mulder2@gmx.de> */

/*libsndfile*/
#define ENABLE_SNDFILE_WINDOWS_PROTOTYPES 1
#include <sndfile.h>

/*CRT*/
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>

/*Const*/
static const size_t BUFF_SIZE = 2048;

/* Scan audio samples */
static void analyze_samples(double &max_sample, const double *const buffer, const long long count, const int channels)
{
	for (long long i = 0; i < count; i++)
	{
		for (int c = 0; c < channels; c++)
		{
			const double current_sample = buffer[(i * channels) + c];
			max_sample = std::max(max_sample, abs(current_sample));
		}
	}
}

/* Process audio samples */
static void process_samples(const double max_sample, double *const buffer, const long long count, const int channels)
{
	const double amplification_factor = 1.0 / max_sample;
	for (long long i = 0; i < count; i++)
	{
		for (int c = 0; c < channels; c++)
		{
			double &current_sample = buffer[(i * channels) + c];
			current_sample *= amplification_factor;
		}
	}
}

/* Main function */
static int example_main(int argc, wchar_t *argv[])
{
	/* Print logo */
	printf("libsndfile-MSVC example application [%s]\n", __DATE__);
	printf("Powered by %s\n\n", sf_version_string());

	/* Check for arguments */
	if (argc < 3)
	{
		printf("Error: Command-line argument is missing!\n\n");
		printf("Usage:\n  example.exe <input_file.wav> <output_file.wav>\n\n");
		return 1;
	}

	/* Initialize SF_INFO struct */
	SF_INFO info_src;
	memset(&info_src, 0, sizeof(SF_INFO));

	/* Open input file */
	printf("Opening source audio file:\n%S\n\n", argv[1]);
	SNDFILE *handle_src = sf_wchar_open(argv[1], SFM_READ, &info_src);

	/* Check for success */
	if (!handle_src)
	{
		printf("Failed to open source audio file for reading:\n%s\n\n", sf_error_number(sf_perror(NULL)));
		return 2;
	}

	/* Initialize SF_INFO struct */
	SF_INFO info_out;
	memset(&info_out, 0, sizeof(SF_INFO));

	/* Setuo outpout format */
	info_out.format = SF_FORMAT_WAV | SF_FORMAT_PCM_16;
	info_out.channels = info_src.channels;
	info_out.samplerate = info_src.samplerate;

	/* Open output file */
	printf("Opening output audio file:\n%S\n\n", argv[2]);
	SNDFILE *handle_out = sf_wchar_open(argv[2], SFM_WRITE, &info_out);

	/* Check for success */
	if (!handle_out)
	{
		printf("Failed to open output audio file for writing:\n%s\n\n", sf_error_number(sf_perror(NULL)));
		sf_close(handle_src);
		return 3;
	}

	/* Print some info */
	printf("[File Information]\n");
	printf("File format identifier: 0x%X\n", info_src.format);
	printf("Number of channels: %d\n", info_src.channels);
	printf("Sampling rate: %d Hz\n", info_src.samplerate);
	printf("Duration, in frames: %lld\n", info_src.frames);
	printf("Is seekable: %s\n\n", info_src.seekable ? "YES" : "NO");

	/* Allocate buffer */
	double *buffer = new double[BUFF_SIZE * info_src.channels];

	/* Simple 2-pass normalization algorithm */
	static double max_sample = 0.0;
	for (int pass = 0; pass < 2; ++pass)
	{
		/* Loop over the entire file */
		printf("Pass %d/2: %s audio samples, please wait...\n", pass + 1, pass ? "Process" : "Analyze");
		long long count = BUFF_SIZE, total_samples = 0;
		while (count >= BUFF_SIZE)
		{
			/* Read next chunk auf data */
			count = sf_readf_double(handle_src, &buffer[0], BUFF_SIZE);

			/* Process read audio data */
			if (count > 0)
			{
				if (pass > 0)
				{
					/* Processing pass */
					process_samples(max_sample, buffer, count, info_src.channels);

					/* Write out processed samples */
					if (count != sf_writef_double(handle_out, &buffer[0], count))
					{
						printf("Error: Failed to write data to audio file!\n\n");
						delete[] buffer;
						sf_close(handle_out);
						sf_close(handle_src);
						return 4;
					}
				}
				else
				{
					/* Analysis pass */
					analyze_samples(max_sample, buffer, count, info_src.channels);
				}

				/* Bookkeeping */
				total_samples += count;
			}

			/* Update progress indicator */
			if (info_src.frames > 0)
			{
				const double percentage = ((double)total_samples) / ((double)info_src.frames) * 100.0;
				printf("\r%lld/%lld [%.1f%%]", total_samples, info_src.frames, percentage);
			}
			else
			{
				printf("\r%lld", total_samples);
			}
		}
		printf("\n\n");

		/*Rewind file*/
		if (sf_seek(handle_src, 0, SEEK_SET) != 0)
		{
			printf("Error: Failed to rewind audio file!\n\n");
			delete[] buffer;
			sf_close(handle_out);
			sf_close(handle_src);
			return 5;
		}
	}


	/* Completed */
	printf("Everything completed succesfully.\n\n");

	/* Clean up the mess */
	delete[] buffer;
	sf_close(handle_out);
	sf_close(handle_src);

	/* Time to say goodbye */
	return 0;
}

/* Entry point */
int wmain(int argc, wchar_t *argv[])
{
#ifndef _DEBUG
	__try
	{
		return example_main(argc, argv);
	}
	__except (1)
	{
		fputs("\n\nFATAL ERROR: Unhandeled excaption error :-(\n\n", stderr);
		_exit(666);
	}
#else
	return example_main(argc, argv);
#endif
}
