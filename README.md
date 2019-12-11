# eegl64
Random Number Generator using 16384 linear feedback shift registers.
The period length of this RNG is extended by using a Bays-Durham
shuffle.  The weaknesses inherent in an LFSR generator are overcome
by using the Bays-Durham shuffle.  This generator is more "random"
than a plain LFSR generator.

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
present in dieharder.

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
Twister and TAUS are compared to the results of this
generator.  The results of all three generators are very
close and juggle back and forth in each instance of the test.

Read INSTALL, TESTING, and README.eegl for more information.
