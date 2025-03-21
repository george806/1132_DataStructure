#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Player {  /*���a���c��ƫ��A�A�]�tstring���������a�W�٥H��int���������a����*/
    string name;
    int score;
};

int drawCard() {
    return rand() % 10 + 1; /*�o�P�\��A�I�s�@���o�@�i�ƭȦb1-10�������P*/
}

// ��l�ƪ��a
void initializePlayer(Player* player, string name) {
	int n=drawCard()+drawCard();//�����i��l��� 
	player->score=n;//���P����ƤH 
	player->name=name;//��W�r����ƤH 
    /*�Q�ΤW�������c�ܼơA�F�짹����l�ƪ��a�åB�P�ɵo��i��l��P*/
}
// ��ܪ��a����
void displayScore(Player* player) {
	cout<<player->name<<"������:"<<player->score<<"\n"; 
    /*��ܪ��a��e����P�I��*/
}
// ���a�^�X
void playerTurn(Player* player) {
    char choice;
	bool k=false;//�P�_�O�_���Ace 
    while (player->score < 21) {
        cout << "�n��P�ܡH(h = ��, s = ��) : ";
        cin >> choice;
        if (choice == 'h') {
        	int i=drawCard();
			player->score+=i;//��s���d�å[��w���P�w 
        	if(player->score<=10&&i==1){//�p�G�����Ƥp��10����Ace�|�Q��@11 
        		player->score+=10;
        		k=true;
			}
			if(k!=false&&player->score>21){ //�W�X21��ݦ��S��Ace���N�⥦��@1 
				player->score+=-10;
				k=false;
			} 
			cout<<"��� "<< i<<"�I�A�ثe�`��:"<< player->score<<"\n";//��ܥثe�I�� 
            //��P���ܡF�ŧi�@���ܼƦA�I�s��P���
            /*�N�s��쪺��P�I�ƥ[�W�쥻���a�֦�����P�I�ơA�å��L�X�ӷ�e���a��P�`�I��*/
            if (player->score > 21) {
                cout << player->name << " �z���F�I�C�������C\n";
                return;
            }
        }
        else if (choice == 's') {
            break;
        }
    }
}

// ���a�^�X
void dealerTurn(Player* dealer) {
	bool k=false;//�P�_�O�_���Ace 
    while (dealer->score < 17) { // ���a�ܤ֭n�� 17 �I
    	int i=drawCard();
    	dealer->score+=i;//��P�å[��P�w 
		if(dealer->score<=10&&i==1){//�p�G�����Ƥp��10����Ace�|�Q��@11 
    		dealer->score+=10;
    		k=true;
		}
		if(k!=false&&dealer->score>21){ //�W�X21��ݦ��S��Ace���N�⥦��@1 
			dealer->score+=-10;
			k=false;
		} 
        //��P���ܡF�ŧi�@���ܼƦA�I�s��P���
        /*�p�G���a�I�Ƥp��17�A�h�ܤ֫���W�[��P�Ȩ���a��P�I�Ƥj�󵥩�17�A�ñN���a��P�I�ƥ��L�X��*/
        cout << "���a���" << i << "�I�A�ثe�`��: " << dealer->score << endl;
        
        if (dealer->score > 21) { // �p�G���a�W�L 21 �I
            cout << "���a�z�F�I���a��ӡI" << endl;
            return; // �C������
        }
    }
}
// �P�_�ӭt
void determineWinner(Player* player, Player* dealer) {
    if (player->score > 21) {
        cout << "�A�z�F�I���a��ӡI\n";
    }
    else if (dealer->score > 21 || player->score > dealer->score) {
        cout << "�AĹ�F�I!\n";
    }
    else if (player->score == dealer->score) {
        cout << "����I\n";
    }
    else {
        cout << "���aĹ�F�I\n";
    }
}

// �D�{��
int main() {
    srand(time(0));

    Player player, dealer;//�����a�M���a 
    initializePlayer(&player, "���a");//���t�W�r�M��P 
    initializePlayer(&dealer, "���a");

    displayScore(&player);
    playerTurn(&player);//�}�l��P 

    if (player.score <= 21) { // �p�G�S�z�~�����a�^�X
        cout << "\n���a�^�X...\n";
        displayScore(&dealer);
        dealerTurn(&dealer);
        determineWinner(&player, &dealer);
    }

    return 0;
}
