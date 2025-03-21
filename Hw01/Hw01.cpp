#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Player {  /*玩家結構資料型態，包含string類型的玩家名稱以及int類型的玩家分數*/
    string name;
    int score;
};

int drawCard() {
    return rand() % 10 + 1; /*發牌功能，呼叫一次發一張數值在1-10之間的牌*/
}

// 初始化玩家
void initializePlayer(Player* player, string name) {
	int n=drawCard()+drawCard();//收到兩張初始手排 
	player->score=n;//把手牌給當事人 
	player->name=name;//把名字給當事人 
    /*利用上面的結構變數，達到完成初始化玩家並且同時發兩張初始手牌*/
}
// 顯示玩家分數
void displayScore(Player* player) {
	cout<<player->name<<"的分數:"<<player->score<<"\n"; 
    /*顯示玩家當前的手牌點數*/
}
// 玩家回合
void playerTurn(Player* player) {
    char choice;
	bool k=false;//判斷是否抽到Ace 
    while (player->score < 21) {
        cout << "要抽牌嗎？(h = 抽, s = 停) : ";
        cin >> choice;
        if (choice == 'h') {
        	int i=drawCard();
			player->score+=i;//抽新的卡並加到已有牌庫 
        	if(player->score<=10&&i==1){//如果持有數小於10那麼Ace會被當作11 
        		player->score+=10;
        		k=true;
			}
			if(k!=false&&player->score>21){ //超出21後看有沒有Ace有就把它當作1 
				player->score+=-10;
				k=false;
			} 
			cout<<"抽到 "<< i<<"點，目前總分:"<< player->score<<"\n";//顯示目前點數 
            //抽牌提示；宣告一個變數再呼叫抽牌函數
            /*將新抽到的手牌點數加上原本玩家擁有的手牌點數，並打印出來當前玩家手牌總點數*/
            if (player->score > 21) {
                cout << player->name << " 爆掉了！遊戲結束。\n";
                return;
            }
        }
        else if (choice == 's') {
            break;
        }
    }
}

// 莊家回合
void dealerTurn(Player* dealer) {
	bool k=false;//判斷是否抽到Ace 
    while (dealer->score < 17) { // 莊家至少要到 17 點
    	int i=drawCard();
    	dealer->score+=i;//抽牌並加到牌庫 
		if(dealer->score<=10&&i==1){//如果持有數小於10那麼Ace會被當作11 
    		dealer->score+=10;
    		k=true;
		}
		if(k!=false&&dealer->score>21){ //超出21後看有沒有Ace有就把它當作1 
			dealer->score+=-10;
			k=false;
		} 
        //抽牌提示；宣告一個變數再呼叫抽牌函數
        /*如果莊家點數小於17，則至少持續增加手牌值到莊家手牌點數大於等於17，並將莊家手牌點數打印出來*/
        cout << "莊家抽到" << i << "點，目前總分: " << dealer->score << endl;
        
        if (dealer->score > 21) { // 如果莊家超過 21 點
            cout << "莊家爆了！玩家獲勝！" << endl;
            return; // 遊戲結束
        }
    }
}
// 判斷勝負
void determineWinner(Player* player, Player* dealer) {
    if (player->score > 21) {
        cout << "你爆了！莊家獲勝！\n";
    }
    else if (dealer->score > 21 || player->score > dealer->score) {
        cout << "你贏了！!\n";
    }
    else if (player->score == dealer->score) {
        cout << "平手！\n";
    }
    else {
        cout << "莊家贏了！\n";
    }
}

// 主程式
int main() {
    srand(time(0));

    Player player, dealer;//分莊家和玩家 
    initializePlayer(&player, "玩家");//分配名字和手牌 
    initializePlayer(&dealer, "莊家");

    displayScore(&player);
    playerTurn(&player);//開始抽牌 

    if (player.score <= 21) { // 如果沒爆才讓莊家回合
        cout << "\n莊家回合...\n";
        displayScore(&dealer);
        dealerTurn(&dealer);
        determineWinner(&player, &dealer);
    }

    return 0;
}
