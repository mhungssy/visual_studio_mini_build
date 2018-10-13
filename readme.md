## make file .lib from .dll & Configure Visual Studio build minimal exe/dll 

### Make file *.lib* from *.dll*

1. Open cmd.exe

2. Set add VC path to enviroment *PATH* variable

		set PATH=%PATH%;C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\bin
		REM in my case is Visual Studio 2013
		REM replace path to your Visual Studio installed version
	
3. Dump export symbol form you dll

		dumpbin /EXPORTS C:\Windows\System32\msvcrt.dll > D:\imsvcrt.def
	
4. Remove unnecessary text, only keep exports symbol

- dumpbin export follow

		Microsoft (R) COFF/PE Dumper Version 12.00.21005.1
		Copyright (C) Microsoft Corporation.  All rights reserved.


		Dump of file C:\Windows\System32\msvcrt.dll

		File Type: DLL

		  Section contains the following exports for msvcrt.dll

			00000000 characteristics
			5CBBA6FD time date stamp Sun Apr 21 00:10:53 2019
				0.00 version
				   1 ordinal base
				1317 number of functions
				1317 number of names

			ordinal hint RVA      name

			  1    0 0000A440 ??0__non_rtti_object@@QEAA@AEBV0@@Z
			  2    1 0000A470 ??0__non_rtti_object@@QEAA@PEBD@Z
			  3    2 0000A4A0 ??0bad_cast@@AAE@PBQBD@Z
			  4    3 0000A4A0 ??0bad_cast@@AEAA@PEBQEBD@Z
			  5    4 0000A4A0 ??0bad_cast@@QAE@ABQBD@Z
			  6    5 0000A4A0 ??0bad_cast@@QEAA@AEBQEBD@Z
			...
			1307  51A 000059A0 wcstombs
			1308  51B 000059B0 wcstombs_s
			1309  51C 00005520 wcstoul
			1310  51D 0005CB80 wcsxfrm
			1311  51E 00006810 wctob
			1312  51F 00005C20 wctomb
			1313  520 00005C60 wctomb_s
			1314  521 0004B930 wprintf
			1315  522 0004B9E0 wprintf_s
			1316  523 0004BB20 wscanf
			
		Summary

			8000 .data
			5000 .pdata
		   19000 .rdata
			1000 .reloc
			1000 .rsrc
		   75000 .text
	   
- After remove unnecessary text and add EXPORTS to begin of file

		EXPORTS
		??0__non_rtti_object@@QEAA@AEBV0@@Z
		??0__non_rtti_object@@QEAA@PEBD@Z
		??0bad_cast@@AAE@PBQBD@Z
		??0bad_cast@@AEAA@PEBQEBD@Z
		??0bad_cast@@QAE@ABQBD@Z
		??0bad_cast@@QEAA@AEBQEBD@Z
		...
		wcstombs
		wcstombs_s
		wcstoul
		wcsxfrm
		wctob
		wctomb
		wctomb_s
		wprintf
		wprintf_s
		wscanf

5. Build .lib from .def file

		lib /DEF:D:\imsvcrt.def /OUT:D:\imsvcrt.lib
	
Now you can use this lib to link with your project


### Configure Visual Studio build minimal exe/dll 

It guid only for C source (C++ is harder, but it possible)

1. Create empty C/C++ project with visual studio

2. On property project, Configuration *Release*

		C/C++ -> Code Genration
			Runtime Library: /MT
			Security Check: /GS-
		Linker -> Input
			Additional Dependencies: imsvcrt.lib
			Ignore All Default Libraries: YES
		Linker -> Advanced
			Entry Point: main
		
