cd data
for /R ".\" %%f in (*.bmp) do (bmp2bin -g %%~nf.bmp %%~nf.bin)
cd m4
for /R ".\" %%f in (*.bmp) do (..\grit %%~nf.bmp  -W3 -ftb -m! -gB8 -p -g -gu8 -pu8 -gb)
mv *.bin ..
del *.h
cd ..
for /R ".\" %%f in (*.bin) do (cl -LV %%~nf.bin -O %%~nf.lz)
exit