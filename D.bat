cd DiO
call D.bat
cd ../tSrv
call D.bat
cd ../_exe
call D.bat
cd ..
del Debug /q
del Release /q
rmdir Debug
rmdir Release
del *.aps
del *.clw
del *.plg
del *.ncb
del *.txt
del DiO.SQL
