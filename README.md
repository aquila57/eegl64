# eegl64
Random Number Generator using 16384 linear feedback shift registers.
The period length of this RNG is extended by using a Bays-Durham
shuffle.  The weaknesses inherent in an LFSR generator are overcome
by using the Bays-Durham shuffle.  This generator is more "random"
than a plain LFSR generator.  This generator passes those random
number generator tests, which a plain LFSR generator fails.

Because of the Bays-Durham shuffle in this RNG, its period
length approximates 16384! generations.  The factorial of
16384 is 1.2 * 10^61036.  This factorial is orders of magnitude
greater than the period length of the Mersenne Twister
generator.

The speed of this generator is equivalent to the speed of
the Mersenne Twister and the TAUS generator.

This generator passes the standard dieharder random number
generator test with the -a parameter.

dieharder -a

The tests in this repository go beyond the dieharder suite
of tests.  In this repository, there are visual tests, not
present in dieharder.  Additional repositories under this
aquila57 account illustrate how the eegl64 generator can
be tested, in comparison to a wide variety of other random
number generators.

The template test in this repository is different from the
template test in dieharder.  The template test used here
is based on a random pattern.  Each time the test is run
the pattern changes.  The main way to fail the template test
is to duplicate the input data.  The template test fails,
when the template is repeated in its entirety.  Of course,
if the input data is not random, the template test also
fails the chi square test predictably.  Read more about
the template test in TESTING.

Almost all other random number test suites shy away from
running Monte Carlo tests.  Seversl Monte Carlo tests are
included in this repository.  The results of Mersenne
Twister and ranlxd2 are compared to the results of this
generator.  The results of all three generators are very
close and juggle back and forth in each instance of the test.

# Eegl generator subroutines.

The following subroutines are kept in a static subroutine
library, called libeegl.a.

* eeglcrc - Generate a crc32 on a random string during
initialization.

* eeglsd - Create a random 32 bit unsigned integer during
initialization.

* eeglinit - Initialize the eegl random number generator.
This routine is based on date and time.  The generator output
is unpredictable.  See eeglstrt for initialization with a seed
parameter.

* eeglstrt - Initialize the eegl random number generator with
a seed parameter.  The generator output is repeatable, and is
used for regression testing.  See eeglinit for initialization
based on date and time.

* eegl - Generate one 32 bit random unsigned integer with a
uniform distribution.  All other formats of output are based
on this subroutine.

* eeglint - Generate a positive random integer between zero
and a limit minus one.

* eeglpwr - Generate from 1 to 32 random bits. 

* eeglbit - Generate one random bit.

* eeglunif - Generate a random fraction from zero to one.
This rountine has 32 bit precision.  See eeglfrac() for
a routine with 53 bit precision.  This routine is faster
than eeglfrac().

* eeglfrac - Generate a random fraction from zero to one.
This rountine has 53 bit precision.  See eeglunif() for
a faster routine with 32 bit precision.

* eegldspl - Display the state of the eegl random number
generator.

* eeglabt - Write a summary of the copyright and license to
stderr.

# Platforms.

This repository may be compiled under Linux.  Examples are
given for the Debian distribution of Linux.  Download the
zip file for the repository into your private source directory.
Unzip the zip file using unzip.  Change to the master directory.
Chmod the install and de-install scripts.  Run inst.sh to compile.

You may also compile this repository under mingw in Windows.
Instead of initializing eegl64 with eeglinit.c, it is easier
to use eeglstrt.c with an initial seed as a parameter.  You
may initialize that seed with date and time, to make your
testing less predictable.  The XWindows programs in this
repository will not run directly under Windows.

See other repositories under this aquila57 account to follow
examples of how to write applications using the eegl64 random
number generator.

Read INSTALL, TESTING, and README.eegl for more information.
