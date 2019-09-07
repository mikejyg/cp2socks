#!/usr/bin/env bash

outfile=sockaddrTest.out
rm $outfile
../mingwDebug/cp2socks sockaddrTest -b | tee $outfile
diff golden/$outfile $outfile
