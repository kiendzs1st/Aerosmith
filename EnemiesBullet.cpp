 #include "EnemiesBullet.h"

using namespace std;

EnemiesBullet::EnemiesBullet(const char* filename, SDL_Renderer* ren, Enemies * enemies)
{
	bulletren = ren;
	bulltext = TextureMana::TextureLoader(filename, bulletren);

	xpos = enemies->GetErect().x - 85;
	ypos = enemies-> GetErect().y + 10;
	src = { 0, 0, 39, 40 };
	dest = { (int)xpos, (int)ypos, src.w, src.h };

}

EnemiesBullet::~EnemiesBullet()
{
	SDL_DestroyTexture(bulltext);
}

void EnemiesBullet::BulletUpdate()
{
	ypos += velocity;
	dest.y = (int)ypos;
	dest.x = (int)xpos;
}

void EnemiesBullet::BulletRender()
{
	SDL_RenderCopy(bulletren, bulltext, &src, &dest);
}

double EnemiesBullet::GetY()
{
	return ypos;
}

SDL_Rect& EnemiesBullet::GetBulletRect()
{
	return dest;
}

int& EnemiesBullet::Velocity()
{
	return velocity;
}