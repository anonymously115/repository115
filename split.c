#include <string.h>
#include <stdlib.h>
#include "split.h"

int split(char* dst[], const char* src, const char* delim, const char* quote){
	//������̕�����
	int n=0;
	//���͕�����̐擪����A��؂蕶������p����T��
	const char* s=src;

	for(;;){//(*1)
		//�o�͗̈���m���ɋ󕶎���ŏ�����
		strcpy(dst[n],"");

		//�J�����p���`�F�b�N
		char* q=strchr(quote,*s);
		
		if(q && *q){//�J�����p���������ꍇ
			//���̈��p�������Ȃ̂�2������1�̈��p����\���̂��s���Ȃ̂ŁA�������[�v�����Ƃ��Ă���
			for(;;){//(*2)
				//�����p������T���i�������p���ŒT���B�������Segmentation fault�ŗ��Ƃ��j
				char* c=strchr(s+1,*s);

				//�J�����p�����ォ������p�����O�܂ł̕����������
				strncat(dst[n],s+1,c-s-1);

				//�����p���̎��̕���
				s=c+1;
				if(*s==*q){//�������p����2������
					//���p����1����
					strncat(dst[n],s,1);
				}else{
					//*c�͕����p���������̂ŁA(*2)�̃��[�v�E�o
					break;
				}
			}
			if(*s=='\0'){
				//�����p���ŕ����񂪏I�������ꍇ�A(*1)�̃��[�v�E�o
				break;
			}
			if(strchr(delim,*s)){//�����p���̎�����؂蕶��
				//���̒T���ʒu��i�߂�
				s++;
			}else{
				//�����p���̎�����؂蕶���ł��I�[�����ł��Ȃ��ꍇ�A�s��
				abort();
			}
		}else{//���p���ȊO
			//��؂蕶���̒���܂��͕�����̐擪����A���̋�؂蕶����T��
			char* c=strpbrk(s, delim);
			
			if(!c){//��؂蕶�����Ȃ�
				//�c��̕����������
				strcat(dst[n],s);

				//(*1)�̃��[�v����E�o
				break;
			}

			//��؂蕶�����O�܂ł̕����������
			strncat(dst[n],s,c-s);

			//���̒T���ʒu�͋�؂蕶���̎�
			s=c+1;
		}

		//������̕����񐔂��C���N�������g���A���̏o�͗̈�Ɋi�[���Ă���
		n++;
	}//(*1)

	//�Ō�ɃC���N�������g���A���ۂ̕�����̕����񐔂�Ԃ�
	return ++n;
}