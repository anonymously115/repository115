#include <string.h>
#include "replace.h"

/*
 * ��������̓���̃e�L�X�g��u������
 * dst : �u����̕�����
 * src : �u�����镶����
 * old : ����������
 * new : �u��������
 * �߂�l : �u����̕�����̐擪�ւ̃|�C���^
 */
char* replace(char* dst, const char* src, const char* old, const char* new){
	if(!strcmp(old,"")){//���������񂪋󕶎��̏ꍇ
		//�u����̕�����ɒu���O�̕�������R�s�[
		strcpy(dst,src);
		
		//�u����̕�����i�̐擪�ւ̃|�C���^�j��Ԃ�
		return dst;
	}

	//�o�͕�������󕶎���ŏ�����
	strcpy(dst, "");
	
	//����������
	int a=(int)strlen(old);
	
	//�u�����镶����̐擪�ւ̃|�C���^
	const char* c=src;

	//�u�����镶����Ɍ��������񂪊܂܂�Ă���΁A���̕����̐擪�ւ̃|�C���^�i�������NULL�j
	char* s=strstr(c,old);
	
	while(s){//�u�����镶����Ɍ��������񂪊܂܂�Ă���
		//����������Ƀq�b�g����܂ł̕�������o�͕�����Ɍ���
		strncat(dst,c,s-c);

		//�o�͕�����ɒu�������������
		strcat(dst,new);

		//���̌����ʒu�̓q�b�g��������������̖����̎�
		c=s+a;

		//���̌����������T������
		s=strstr(c,old);
	}

	//�Ō�̌���������ȍ~�̕�������o�͕�����Ɍ�������
	strcat(dst,c);

	//�u����̕�����̐擪�ւ̃|�C���^��Ԃ�
	return dst;
}