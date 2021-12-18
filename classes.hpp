#pragma once

class SpaceObject
{
public:
    float x, y, w, h; //координаты игрока х и у, высота ширина

    String File;
    Image image;
    Texture texture;
    Sprite sprite;

    SpaceObject(String FileName, float X, float Y, float W, float H/*, float orX, float orY*/)
    {
        File = FileName;//им€ файла+расширение
        w = W; h = H;//высота и ширина
        image.loadFromFile("images\\" + File);//запихиваем в image изображение; вместо File передадим то, что пропишем при создании объекта.
        texture.loadFromImage(image);//закидываем изображение в текстуру
        sprite.setTexture(texture);//заливаем спрайт текстурой
        x = X; y = Y;//координата по€влени€ спрайта
        sprite.setTextureRect(IntRect(0, 0, w, h)); //«адаем спрайту один пр€моугольник. IntRect - приведение типов
        sprite.setPosition(x, y);
        /*sprite.setOrigin(orX, orY);*/
    }
    ~SpaceObject()
    {}

};

class Background
{
public:

    Sprite sprite;

    Background(String FileName, float X, float Y)
    {
        x = X; y = Y;
        File = FileName;
        image.loadFromFile("images\\" + File);
        texture.loadFromImage(image);
        sprite.setTexture(texture);
        sprite.setTextureRect(IntRect(0, 0, x, y));
        sprite.setPosition(0, 0);
    }
    ~Background()
    {}

private:
    float x, y;
    Image image;
    Texture texture;
    String File;
};
