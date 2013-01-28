IDENTIFICATION             DIVISION.
 PROGRAM-ID.                LST001.
 ENVIRONMENT                DIVISION.
 INPUT-OUTPUT               SECTION.
 FILE-CONTROL.
     SELECT  F1  ASSIGN  TO  "C:\COBOL\LST001.CBL"  STATUS  FST.
 DATA                       DIVISION.
 FILE                       SECTION.
 FD  F1.
 01  F1R                    PIC X(72).
 WORKING-STORAGE            SECTION.
 01  FST                    PIC X(02).
 PROCEDURE                  DIVISION.
     OPEN  INPUT  F1
     PERFORM  UNTIL  FST  NOT  =  "00"
         READ  F1
             END
                CONTINUE
             NOT END
                DISPLAY  F1R
         END-READ
     END-PERFORM
     CLOSE  F1
  STOP RUN.