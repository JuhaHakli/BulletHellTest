#include "bulletlogic.h"

void aLinearMove(aBullet &bullet)
{
    //cout << "Luoti Liikkuu" << endl;
    //Muutetaan kulma radiaaneiksi * 10;
    float angRadian = bullet.angle * TORAD;

    float xMovement = bullet.speed * cos(angRadian);
    float yMovement = bullet.speed * sin(angRadian);

    bullet.x += xMovement;
    bullet.y += yMovement;
}

void bLinearMove(bBullet bullet)
{
    bullet.x += bullet.xSpeed;
    bullet.y += bullet.ySpeed;
}
