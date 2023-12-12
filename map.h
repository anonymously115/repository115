/* �A�z�z��\���� */
typedef struct MAP* MAP;

/* �R���X�g���N�^ */
MAP newMap();

/* �L�[�ƒl���Z�b�g�i�L�[�����ɑ��݂��Ă����update, �������insert�̖����j */
void setValue(MAP map, const char* key, void* value);

/* �l���擾 */
void* getValue(MAP map, const char* key);

/* �A�z�z����̑S�ẴL�[�A�l�ɑ΂��ď��� */
void foreach(MAP map, void (*func)(const char* key, const void* value));

/* �A�z�z����̃L�[���폜 */
void* erase(MAP map, const char* key);

/* �A�z�z����������i�v���O�����I�����ɖY��Ȃ�!!�j */
void clear(MAP map, int flag);