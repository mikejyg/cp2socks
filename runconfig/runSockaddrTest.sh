#!/usr/bin/env bash

outfile=sockaddrTest.out
rm $outfile
../Debug/cp2socks sockaddrTest -b | tee $outfile
diff golden/$outfile $outfile
