% libsndfile for MSVC


# About #

Static **libsndfile** for use with *Microsoft Visual C++*, ported by LoRd_MuldeR &lt;<mulder2@gmx.de>&gt;

## Details ##

[**Libsndfile**](http://www.mega-nerd.com/libsndfile/) is a C library for reading and writing files containing sampled sound (such as MS Windows WAV and the Apple/SGI AIFF format) through one standard library interface. Unfortunately, the "official" version of *libsndfile* does **not** currently support building the library with *Microsoft Visual C++* (MSVC). It is still possible to build a Windows DLL of *libsndfile* with [MinGW/GCC](http://mingw-w64.sourceforge.net/) and then link the MinGW-compiled DLL against your MSVC-compiled program files. However, to the best of my knowledge, this method does **not** work if you intend to link *libsndfile* as a ***static*** library! At least I never got it to work ;-)

The purpose of this repository is providing solution/project files that can be used to compile the latest version of *libsndfile* under MSVC, resulting in a "native" MSVC library that allows for **static** linking with MSVC-compiled programs. The code in this repository is identical to the "official" *libsndfile* codebase, except that solution/project files for MSVC have been added and that <tt>config.h</tt> has been adjusted. Furthermore, a few compatibility (build) fixes were required for MSVC, some of which were backported from [Audacity](http://audacity.sourceforge.net/). In my tests, the MSVC binary of *libsndfile* is only slightly slower than the MinGW one.

My project/solution files have been tested to build smoothly under Visual Studio 2013 (MSVC 12.0) or 2015 (MSVC 14.0).


# Legal Notice #

**Libsndfile** was created by *Erik de Castro Lopo* &lt;<erikd@mega-nerd.com>&gt; and is released under the terms of the *GNU Lesser General Public License*. For details, please refer to the official *libsndfile* web-site!

Support for **Ogg**, **Vorbis** and **FLAC** is enabled using "extra" libraries created by *Monty* &lt;<monty@xiph.org>&gt; and the rest of the [Xiph.org Foundation](https://www.xiph.org/). Those libraries are released under the "BSD-style" license.

## Warning ##

Even though *libsndfile* is released under the *GNU Lesser General Public License*, which explicitly *does* allow linking the library (i.e. libsndfile) against proprietary programs, this is *only* applicable as long as the library (i.e. libsndfile) remains *separate* from the proprietary portion of the program &ndash; in the form of a **shared** library. However, as soon as the library (i.e. libsndfile) is linked **statically** into your program, your program *as a whole* **must** be released under the *GNU General Public License*!


# Build Prerequisites

In order to build libsndfile-MSVC with Vorbis and FLAC support enabled, you need the "extra" libraries by Xiph.org:
```
BaseDirectory\
├─ libsndfile-MSVC\
│  ├─ libsndfile_VS2015.sln
│  ├─ libsndfile_VS2015.vcxproj
│  └─ [...]
└─ Prerequisites\
   └─ XiphAudioLibs\
      ├─ include\
      │  ├─ FLAC\
      │  │  ├─ stream_decoder.h
      │  │  ├─ stream_encoder.h
      │  │  └─ metadata.h
      │  ├─ ogg\
      │  │  ├─ ogg.h
      │  │  └─ os_types.h
      │  └─ vorbis\
      │     ├─ codec.h
      │     ├─ vorbisenc.h
      │     └─ vorbisfile.h
      └─ lib\
         └─ Win32\
            └─ static\
               ├─ libFLAC_static.v140_xp.lib
               ├─ libogg_static.v140_xp.lib
               └─ libvorbis_static.v140_xp.lib
```

# Source Code #

The source code of **libsndfile for MSVC** is available from our *Git* mirrors:

* https://github.com/lordmulder/libsndfile-MSVC.git &ndash; [[Browse]](https://github.com/lordmulder/libsndfile-MSVC)

* https://bitbucket.org/muldersoft/libsndfile-msvc.git &ndash; [[Browse]](https://bitbucket.org/muldersoft/libsndfile-msvc)

* https://gitlab.com/lord_mulder/libsndfile-MSVC.git &ndash; [[Browse]](https://gitlab.com/lord_mulder/libsndfile-MSVC)

&nbsp;

e.o.f.
