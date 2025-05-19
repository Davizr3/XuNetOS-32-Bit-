#######################
# XuNet OS Makefile�ļ�
# B Y : I N B O R A 
#######################


TOOLPATH = ./z_tools/
INCPATH  = ./z_tools/XuNetInclude/

MAKE     = $(TOOLPATH)make.exe -r
EDIMG    = $(TOOLPATH)edimg.exe
COPY     = copy
DEL      = del

default :
	$(MAKE) XuNet_OS.img


XuNet_OS.img : kernel/ipl20.bin kernel/XuNet_OS.sys Makefile 
	$(EDIMG)   imgin:./z_tools/fdimg0at.tek \
		wbinimg src:kernel/ipl20.bin len:512 from:0 to:0 \
		copy from:kernel/XuNet_OS.sys to:@: \
		copy from:kernel/ipl20.nas to:@: \
		copy from:apps/type/type.hel to:@: \
		copy from:apps/date/date.hel to:@: \
		copy from:apps/tview/tview.hel to:@: \
		copy from:apps/gview/gview.hel to:@: \
		copy from:apps/about/about.hel to:@: \
		copy from:apps/music/music.hel to:@: \
		copy from:apps/invader/invader.hel to:@: \
		copy from:apps/calc/calc.hel to:@: \
		copy from:apps/pc/pc.hel to:@: \
		copy from:apps/pc/logo.IS to:@: \
		copy from:apps/2dball/2dball.hel to:@: \
		copy from:apps/hview/hview.hel to:@: \
		copy from:apps/note/note.hel to:@: \
		copy from:apps/csvv/csvv.hel to:@: \
		copy from:apps/cpuid/cpuid.hel to:@: \
		copy from:apps/cvtg/cvtg.hel to:@: \
		copy from:apps/csvv/csvv.hel to:@: \
		copy from:apps/csvv/csvv.hel to:@: \
		copy from:apps/video/video.hel to:@: \
		copy from:apps/mtorz/mtorz.hel to:@: \
		copy from:data/daigo.mld to:@: \
		copy from:data/daiku.mld to:@: \
		copy from:data/star.mld to:@: \
		copy from:data/a.htm to:@: \
		copy from:data/moon.txt to:@: \
		copy from:data/dog.jpg to:@: \
		copy from:data/XuNet.vdo to:@: \
		copy from:data/help.txt to:@: \
		copy from:data/chinese/HZK16.fnt to:@: \
		copy from:data/XuNetos.jpg to:@: \
		copy from:data/LOGO.bmp to:@: \
		copy from:data/1.csv to:@: \
		imgout:XuNet_OS.img


run :
	$(MAKE) XuNet_OS.img
	$(COPY) XuNet_OS.img .\z_tools\qemu\fdimage0.bin
	$(MAKE) -C ./z_tools/qemu



full :
	$(MAKE) -C haribote
	$(MAKE) -C apilib
	$(MAKE) -C date
	$(MAKE) -C type
	$(MAKE) -C gview
	$(MAKE) -C tview
	$(MAKE) -C about
	$(MAKE) -C counter
	$(MAKE) -C mmlplay
	$(MAKE) -C invader
	$(MAKE) -C calc
	$(MAKE) XuNet_OS.img

run_full :
	$(MAKE) full
	$(COPY) XuNet_OS.img .\z_tools\qemu\fdimage0.bin
	$(MAKE) -C ./z_tools/qemu

run_os :
	$(MAKE) -C XuNet_OS
	$(MAKE) run

clean :