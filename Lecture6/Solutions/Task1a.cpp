#include <iostream>
using namespace std;

#define MAX_BULLETS 20

using  Bullets = struct Bullets{
unsigned bullet;
struct Bullets* next;
};

void charge(Bullets **bul);
void fire(Bullets **bul);
void free_magazine(Bullets* bul);

int main(){
	Bullets* magazine;
	magazine = new Bullets;
	magazine->bullet = 0;
	magazine->next = NULL;
	charge(&magazine);
	charge(&magazine);
	fire(&magazine);
	charge(&magazine);
	fire(&magazine);
	fire(&magazine);
	fire(&magazine);
	free_magazine(magazine);
	return 0;
}

void charge(Bullets **bul){
    if ((*bul)->bullet >= MAX_BULLETS){
      cout << "Magazine is full!\n";  
    }
    Bullets *tmp = new Bullets;
    tmp->next = *bul;
    tmp->bullet = (*bul)->bullet+1;
    cout << "Bullet " << (*bul)->bullet + 1 << " Added !\n";
    *(bul) = tmp;
    
}

void fire(Bullets **bul){
    Bullets *tmp = (*bul)->next;
    if ((*bul)->next == NULL){
        cout << "Magazine is Empty !\n";
        return ;
    }else {
        cout << "Fired Bullet " << (*bul)->bullet << "!\n";
        delete *bul;
        (*bul) = tmp;
        return;
    }
}
void free_magazine(Bullets* bul){
    if (bul->next == NULL && bul->bullet == 0){
        delete bul;
        return ;
    }
    free_magazine(bul->next);
    delete bul;
    return;
}