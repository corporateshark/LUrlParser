Unit tests based on GoogleTest

Build and Run
-------------
Run 'make' and './tests'

If you have libgtest.so or libgtest.a in a special directory, prepend a definition for GTESTPATH on make commandline.

GTESTPATH=/usr/local/special/include make  

Output
--------

$ ./tests
[==========] Running 8 tests from 1 test case.
[----------] Global test environment set-up.
[----------] 8 tests from UrlTest
[ RUN      ] UrlTest.example
[       OK ] UrlTest.example (0 ms)
[ RUN      ] UrlTest.cases
[       OK ] UrlTest.cases (0 ms)
[ RUN      ] UrlTest.ipv6
[       OK ] UrlTest.ipv6 (0 ms)
[ RUN      ] UrlTest.ipv4
[       OK ] UrlTest.ipv4 (0 ms)
[ RUN      ] UrlTest.parens
[       OK ] UrlTest.parens (0 ms)
[ RUN      ] UrlTest.trailingdot
[       OK ] UrlTest.trailingdot (0 ms)
[ RUN      ] UrlTest.specialchars
[       OK ] UrlTest.specialchars (0 ms)
[ RUN      ] UrlTest.escapechars
[       OK ] UrlTest.escapechars (0 ms)
[----------] 8 tests from UrlTest (0 ms total)

[----------] Global test environment tear-down
[==========] 8 tests from 1 test case ran. (0 ms total)
[  PASSED  ] 8 tests.
