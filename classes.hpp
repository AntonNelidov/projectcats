#pragma once

class SpaceObject
{
public:
    float x, y, w, h; //���������� ������ � � �, ������ ������

    String File;
    Image image;
    Texture texture;
    Sprite sprite;

    SpaceObject(String FileName, float X, float Y, float W, float H/*, float orX, float orY*/)
    {
        File = FileName;//��� �����+����������
        w = W; h = H;//������ � ������
        image.loadFromFile("images\\" + File);//���������� � image �����������; ������ File ��������� ��, ��� �������� ��� �������� �������.
        texture.loadFromImage(image);//���������� ����������� � ��������
        sprite.setTexture(texture);//�������� ������ ���������
        x = X; y = Y;//���������� ��������� �������
        sprite.setTextureRect(IntRect(0, 0, w, h)); //������ ������� ���� �������������. IntRect - ���������� �����
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
