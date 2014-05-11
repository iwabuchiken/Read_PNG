------------------------
06/05/2014 13:42:46

	To run the program
------------------------
# Win
pushd C:\WORKS\WS\WS_Android_20130929_122122\IP
.\dist\Debug\MinGW-Windows\ip.exe
.\dist\Debug\MinGW-Windows\ip.exe lena512.pgm -rgb 10,20,50
.\dist\Debug\MinGW-Windows\ip.exe ..\image_processing_Nagao_2\D-4\images\lena512.pgm -rgb 10,10,100 -dst .\images\lena512.ppm -ff -f
.\dist\Debug\MinGW-Windows\ip.exe -rgb 100,100,100 -dst .\images\lena512.ppm -ff -f -src ..\image_processing_Nagao_2\D-4\images\lena512.pgm

# Ubuntu
pushd /home/iwabuchik/WORKS/WS/WS_Prog/Read_PNG
pushd /home/iwabuchik/WORKS/WS/WS_Prog/Read_PNG/images
pushd /home/iwabuchik/WORKS/WS/WS_Prog/Read_PNG/dist/Debug/GNU-Linux-x86/

/home/iwabuchik/WORKS/WS/WS_Prog/Read_PNG/dist/Debug/GNU-Linux-x86/read_png

------------------------

    Ignored by file system
	
------------------------
^(CVS|SCCS|vssver.?\.scc|#.*#|%.*%|_svn)$|~$|^\.(?!htaccess$).*$



================ EOF ================