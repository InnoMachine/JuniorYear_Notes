@ECHO OFF

FOR %%i IN (Exe, Output, Release, Debug, Settings) DO IF EXIST %%i RD %%i /S/Q

FOR %%i IN (EX~, DEP, OPT, PLG, APS, NCB, TMP, ZIP, LOG, ILK, SIO, ERR, TPU, RES) DO IF EXIST *.%%i DEL *.%%i
