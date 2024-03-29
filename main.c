#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char* argv[]) {
    FILE* wf;
    FILE* rf;

    // nand.txt 파일 존재 확인
    if (fopen("nand.txt", "r") == 0) {
        wf = fopen("nand.txt", "w");
        for (int i = 1; i <= 99; i++) {
            if (i <= 9) fprintf(wf, "0%d: 0x00000000\n", i);
            else fprintf(wf, "%d: 0x00000000\n", i);
        }
        fclose(wf);
    }

    /*
    for (int i = 0; i < argc; i++) {
        printf("argv[%d] = %s\n", i, argv[i]);
    }
	*/

    // Write 명령 들어왔을 때
    // 숫자가 한 자리면 0 붙이기
    char num[3];
    if (argc > 1 && strcmp(argv[1], "W") == 0) {
        if (strlen(argv[2]) == 1) {
            sprintf(num, "0%s", argv[2]);
        }
        else strcpy(num, argv[2]);
    }

    // 쓰기 포인터 처음으로


    wf = fopen("nand.txt", "r");

    fseek(wf, 0, SEEK_SET);


    // nand.txt에서 num 줄 찾기
    char lines[100][1000];
    char lineNum[3];

    for (int i = 1; i < 100; i++) {
        fgets(lines[i], sizeof(lines[i]), wf);
    }

    fclose(wf);

    char temp[100];
    int i = 0;

    for (i = 0; i < 100; i++)
    {
        lineNum[0] = lines[i][0];
        lineNum[1] = lines[i][1];
        lineNum[2] = '\0';

        if (strcmp(num, lineNum) == 0) {
            sprintf(temp, "%s: %s\n\0", lineNum, argv[3]);
            strcpy(lines[i], temp);
        }
    }

    wf = fopen("nand.txt", "w");

    for (int i = 1; i < 100; i++) {
        fprintf(wf, lines[i]);
    }

    fclose(wf);



    // Read 명령 들어왔을 때
    // 숫자가 한 자리면 0 붙이기
    char readNum[3];
    

    if (argc > 1 && strcmp(argv[1], "R") == 0) {
        rf = fopen("result.txt", "w");
        // result.txt 파일 존재 확인

        if (strlen(argv[2]) == 1) {
            sprintf(readNum, "0%s", argv[2]);
        }
        else strcpy(readNum, argv[2]);

        fclose(rf);

        wf = fopen("nand.txt", "r");

        fseek(wf, 0, SEEK_SET);


        // nand.txt에서 num 줄 찾기
        char lines2[100][1000];
        char lineNum2[3];

        for (int i = 1; i < 100; i++) {
            fgets(lines2[i], sizeof(lines2[i]), wf);
        }

        fclose(wf);

        char temp2[100];
        char now[1000];

        for (int i = 0; i < 100; i++)
        {
            lineNum2[0] = lines2[i][0];
            lineNum2[1] = lines2[i][1];
            lineNum2[2] = '\0';

            if (strcmp(readNum, lineNum2) == 0) {
                int now_idx = 0;
                for (int idx = 4; lines2[i][idx] != '\0'; idx++) {
                    now[now_idx++] = lines2[i][idx];
                }
                now[now_idx] = '\0';

                sprintf(temp2, "%s\n\0", now);
            }
        }

        rf = fopen("result.txt", "w");

        fprintf(rf, temp2);

        fclose(rf);

    }

   
}
