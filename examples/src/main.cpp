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

/* Dummy processing function */
void process_samples(const double *const buffer, const long long int count, const int channels)
{
	static double max_sample = -1.0;
	for (long long int i = 0; i < count; i++)
	{
		for (int c = 0; c < channels; c++)
		{
			const double current_sample = buffer[(i * channels) + c];
			max_sample = std::max(max_sample, abs(current_sample));
		}
	}
}

/* MAIN */
int wmain(int argc, wchar_t *argv[])
{
	/* Print logo */
	printf("libsndfile-MSVC exmaple application [%s]\n", __DATE__);
	printf("Powered by %s\n\n", sf_version_string());

	/* Check for arguments */
	if (argc < 2)
	{
		printf("Error: Command-line argument is missing!\n\n");
		return -1;
	}

	/* Initialize SF_INFO struct */
	SF_INFO info;
	memset(&info, 0, sizeof(SF_INFO));

	/* Open input file */
	printf("Opening audio file:\n%S\n\n", argv[1]);
	SNDFILE *handle = sf_wchar_open(argv[1], SFM_READ, &info);

	/* Check for success */
	if (!handle)
	{
		printf("Error: Failed to open audio file!\n\n");
		return -1;
	}

	/* Print some info */
	printf("[File Information]\n");
	printf("File format identifier: 0x%X\n", info.format);
	printf("Number of channels: %d\n", info.channels);
	printf("Sampling rate: %d Hz\n", info.samplerate);
	printf("Duration, in frames: %lld\n", info.frames);
	printf("Is seekable: %s\n\n", info.seekable ? "YES" : "NO");

	/* Allocate buffer */
	double *buffer = new double[BUFF_SIZE * info.channels];
	long long int total_samples = 0;
	
	/* Read the entire file */
	long long int count = BUFF_SIZE;
	printf("Processing audio samples, please wait...\n");
	while (count >= BUFF_SIZE)
	{
		count = sf_readf_double(handle, &buffer[0], BUFF_SIZE);
		if (count > 0)
		{
			process_samples(buffer, count, info.channels);
			total_samples += count;
		}

		/* Update progress indicator */
		if (info.frames > 0)
		{
			const double percentage = ((double)total_samples) / ((double)info.frames) * 100.0;
			printf("\r%lld/%lld (%.1f%%)", total_samples, info.frames, percentage);
		}
		else
		{
			printf("\r%lld", total_samples);
		}
	}

	/* Completed */
	printf("\n\nCompleted.\n\n");

	/* Clean up the mess */
	sf_close(handle);
	handle = NULL;
	delete [] buffer;
	buffer = NULL;

	/* Time to say goodbye */
	return 0;
}
