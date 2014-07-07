libsndfile for MSVC
-------------------

[**Libsndfile**](http://www.mega-nerd.com/libsndfile/) is a C library for reading and writing files containing sampled sound (such as MS Windows WAV and the Apple/SGI AIFF format) through one standard library interface. Unfortunately, the "official" version of *libsndfile* does **not** currently support building the library with *Microsoft Visual C++* (MSVC). It's still possible to build a Windows DLL of *libsndfile* with [MinGW](http://mingw-w64.sourceforge.net/), generate a suitable *import library* and then link the MinGW-compiled DLL against your MSVC-compiled program files. However, to the best of my knowledge, this method does **not** work if you intend to link *libsndfile* as a ***static*** library! At least I never got it to work properly ;-)

The purpose of this repository is providing solution/project files that can be used to compile the latest version of *libsndfile* under MSVC, resulting in a "native" MSVC library that allows for **static** linking with MSVC-compiled program files. The code in this repository is is identical to the "official" *libsndfile* code, except that solution/project for MSVC have been added and that the <tt>config.h</tt> (which was generated under MinGW) has been adjusted in order to satisfy the Microsoft compiler. Furthermore, a few compatibility fixes were required, some of which were backported from [Audacity](http://audacity.sourceforge.net/). In my tests, the MSVC build of *libsndfile* is slightly slower than the MinGW one.

## Legal Notice ##

Libsndfile was created by *Erik de Castro Lopo* and is is released under the terms of the *GNU Lesser General Public License*. For details, please refer to the official *libsndfile* web-site!

**Statically** linking *libsndfile* into your program requires that your program is released under GNU GPL !!!
