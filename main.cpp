#include <iostream>
#include <SFML/Graphics.hpp>
#include <list>

using namespace sf;

const int boy = 17;
const int en = 32;

String Harita[boy] = {
        "HHHHHHHHHHHHHH0HH0HHHHHHHHHHHHHH",
        "H    H                  H    H",
        "H    H                  H    H",
        "H    H                       H",
        "H              H             H",
        "H              H             H",
        "H        H     H   HHHH      H",
        "H        H            H      H",
        "H        H            H      H",
        "H        H            H      H",
        "H        HHHH         H      H",
        "H                H    H      H",
        "H                H           H",
        "H                H           H",
        "H                H        H  H",
        "HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH",
        "HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH",
};

// Mermiler icin class yapisi
class Mermi {
public:
    float x, y, xk, yk, g, b, o;
    bool yasiyorMu, o1yasiyorMu, o2yasiyorMu;
    Texture bl;
    Sprite mermi;
    Mermi(int X, int Y, int yon, int oyuncu) {
        x = X;
        y = Y;
        o = oyuncu;
        if (yon == 1) xk = -0.3;
        else if (yon == 2) xk = 0.3;
        else xk = 0;

        if (yon == 3) yk = -0.3;
        else if (yon == 4) yk = 0.3;
        else yk = 0;

        g = b = 15;
        o1yasiyorMu = true;
        o2yasiyorMu = true;
        yasiyorMu = true;
        bl.loadFromFile("/Users/senadulger/Okul/CProgramlama/220229053_SenaNurDulger/extensions/bullet.png");
        mermi.setTexture(bl);
    }
    void güncelle(float zaman, int x1, int y1, int x2, int y2) {
        x += xk * zaman;
        y += yk * zaman;


        for (int i = y / 50; i < (y + b) / 50; i++)
            for (int j = x / 50; j < (x + g) / 50; j++)
                if (Harita[i][j] == 'H') {
                    xk = 0; yk = 0; yasiyorMu = false;
                }
        if (o == 1)
            if (x > x1 && y > y1 && x < (x1 + 100) && y < (y1 + 100)) { yasiyorMu = false; o1yasiyorMu = false; }
        if (o == 2)
            if (x > x2 && y > y2 && x < (x2 + 100) && y < (y2 + 100)) { yasiyorMu = false; o2yasiyorMu = false; }
        mermi.setPosition(x, y);

    }
    void mermiCiz(RenderWindow& pencere) {
        pencere.draw(mermi);
    }
};

// Carpismalar Icin Fonksiyonlar
bool solCarpisma(int x, int y, int s) {
    for (int i = (y + 1) / 50; i < (y + s - 2) / 50; i++) {
        if (Harita[i][x / 50] == 'H') return true;
        else {
            if (Harita[i + 1][x / 50] == 'H') return true;
            else {
                if (Harita[i + 2][x / 50] == 'H') return true;
                else return false;
            }
        }
    }
}

bool sagCarpisma(int x, int y, int s) {
    for (int i = (y + 1) / 50; i < (y + s - 2) / 50; i++) {
        if (Harita[i][(x + 100) / 50] == 'H') return true;
        else {
            if (Harita[i + 1][(x + 100) / 50] == 'H') return true;
            else {
                if (Harita[i + 2][(x + 100) / 50] == 'H') return true;
                else return false;
            }
        }
    }
}

bool ustCarpisma(int x, int y, int s) {
    for (int j = (x + 1) / 50; j < (x + s) / 50; j++) {
        if (Harita[y / 50][j] == 'H') return true;
        else {
            if (Harita[y / 50][j + 1] == 'H') return true;
            else {
                if (Harita[y / 50][j + 2] == 'H') return true;
                else return false;
            }
        }
    }
}

bool altCarpisma(int x, int y, int s) {
    for (int j = (x + 1) / 50; j < (x + s) / 50; j++) {
        if (Harita[(y + 100) / 50][j] == 'H') return true;
        else {
            if (Harita[(y + 100) / 50][j + 1] == 'H') return true;
            else {
                if (Harita[(y + 100) / 50][j + 2] == 'H') return true;
                else return false;
            }
        }
    }
}

int main() {

    // Mermi sinifinin isaretcilerini saklamak için olusturulan liste
    std::list<Mermi*> mermiler;
    // Listenin icindeki elemanlari dolasmak icin olusturulan iterator
    std::list<Mermi*>::iterator it;

    // Giris ekraninin penceresinin olusturulmasi
    RenderWindow girisPenceresi(VideoMode(1600, 900), "AZ Tank Game");

    // Oyunda kullanilacak yazi stilini ekleme
    Font font;
    if (!font.loadFromFile("/Users/senadulger/Okul/CProgramlama/220229053_SenaNurDulger/extensions/Copyduck.ttf"))
    {
        // Yazi tipi yuklenemedi hatasi
        return -1;
    }

    // Giris ekrani dizayni
    Texture giris;
    giris.loadFromFile("/Users/senadulger/Okul/CProgramlama/220229053_SenaNurDulger/extensions/entry.jpg");
    Sprite girisE;
    girisE.setTexture(giris);

    // Giris ekraninin dizayni
    Text oyunAdi("AZ Tank Game", font, 50);
    oyunAdi.setFillColor(Color::White);
    oyunAdi.setStyle(Text::Bold);
    oyunAdi.setPosition(600, 300);

    // Baslangic metni
    Text baslat("Baslamak icin 'Enter' tusuna basin", font, 30);
    baslat.setFillColor(Color::White);
    baslat.setPosition(500, 500);

    // Giris ekraninin acik kalmasi
    bool girisEkraniniGecme = true;
    while (girisPenceresi.isOpen() && girisEkraniniGecme) {
        Event girisEvent;
        while (girisPenceresi.pollEvent(girisEvent)) {
            if (girisEvent.type == Event::Closed)
                girisPenceresi.close();
            if (girisEvent.type == Event::KeyPressed && girisEvent.key.code == Keyboard::Enter)
                girisEkraniniGecme = false;
        }

        // Giris penceresindeki tüm nesneler ekrana cizilir
        girisPenceresi.draw(girisE);
        girisPenceresi.draw(oyunAdi);
        girisPenceresi.draw(baslat);
        girisPenceresi.display();
    }

    // Oyun ekraninin penceresinin olusturulmasi
    RenderWindow pencere(VideoMode(1600, 900), "AZ Tank Game"); // Oyun Penceresi

    // Skor yazilarinin dizayni
    Text skorMetni;
    Text skorMetni1;
    skorMetni.setFont(font);
    skorMetni1.setFont(font);
    skorMetni.setCharacterSize(45);
    skorMetni1.setCharacterSize(45);
    skorMetni.setFillColor(Color::Red);
    skorMetni1.setFillColor(Color::Blue);

    // Kirmizi tankin dizayni
    Texture kirmiziTank;
    kirmiziTank.loadFromFile("/Users/senadulger/Okul/CProgramlama/220229053_SenaNurDulger/extensions/redTank.png");
    Sprite s;
    s.setTexture(kirmiziTank);
    s.setTextureRect(IntRect(300, 0, 100, 100));
    s.setPosition(1300, 400);  // Ilk tankin baslangic konumu

    // Mavi tankin dizayni
    Texture maviTank;
    maviTank.loadFromFile("/Users/senadulger/Okul/CProgramlama/220229053_SenaNurDulger/extensions/blueTank.png");
    Sprite s2;
    s2.setTexture(maviTank);
    s2.setTextureRect(IntRect(100, 0, 100, 100));
    s2.setPosition(100, 400); // Ikinci tankin baslangic konumu

    // Engellerin dizayni
    Texture engel;
    engel.loadFromFile("/Users/senadulger/Okul/CProgramlama/220229053_SenaNurDulger/extensions/block.jpg");
    Sprite e;
    e.setTexture(engel);

    // Arkaplanin dizayni
    Texture zemin;
    zemin.loadFromFile("/Users/senadulger/Okul/CProgramlama/220229053_SenaNurDulger/extensions/background.jpeg");
    Sprite z;
    z.setTexture(zemin);

    // Sonuc ekraninin dizayni
    // Kirmizi tank kazanirsa;
    Texture ktkazandi;
    ktkazandi.loadFromFile("/Users/senadulger/Okul/CProgramlama/220229053_SenaNurDulger/extensions/rWon.png");
    Sprite t1kazandi;
    t1kazandi.setTexture(ktkazandi);
    t1kazandi.setPosition(0, 0);

    // Mavi tank kazanirsa;
    Texture mtkazandi;
    mtkazandi.loadFromFile("/Users/senadulger/Okul/CProgramlama/220229053_SenaNurDulger/extensions/bWon.png");
    Sprite t2kazandi;
    t2kazandi.setTexture(mtkazandi);
    t2kazandi.setPosition(0, 0);

    int durum1 = 1;
    int durum2 = 2;
    bool oyunBitti = false;
    int oyuncu1Skor = 0;
    int oyuncu2Skor = 0;

    // Oyun dongusu icinde gecen zamani olcmek icin bir saat olusturulur
    Clock clock;
    while (pencere.isOpen() && oyunBitti == false) {
        float zaman = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        zaman = zaman / 500;

        // Tanklarin vurus tuslarini belirleme
        Event olay;
        while (pencere.pollEvent(olay)) {
            if (olay.type == Event::Closed)
                pencere.close();
            if (olay.type == Event::KeyPressed)
                if (olay.key.code == Keyboard::L)
                    mermiler.push_back(new Mermi(s.getPosition().x + 43, s.getPosition().y + 43, durum1, 2));   // Oyuncu 2'nin mermisi
            if (olay.type == Event::KeyPressed)
                if (olay.key.code == Keyboard::V)
                    mermiler.push_back(new Mermi(s2.getPosition().x + 43, s2.getPosition().y + 43, durum2, 1)); // Oyuncu 1'in mermisi
        }

        int sinir = 100;
    // Oyuncu 2'nin hareketi
    if (Keyboard::isKeyPressed(Keyboard::Left)) {
        if (solCarpisma(s.getPosition().x, s.getPosition().y, sinir) == 0) s.move(-0.1 * zaman, 0);
        s.setTextureRect(IntRect(300, 0, 100, 100));
        durum1 = 1;
    }
    else {
        if (Keyboard::isKeyPressed(Keyboard::Right)) {
            if (sagCarpisma(s.getPosition().x, s.getPosition().y, sinir) == 0) s.move(0.1 * zaman, 0);
            s.setTextureRect(IntRect(100, 0, 100, 100));
            durum1 = 2;
        }
        else {
            if (Keyboard::isKeyPressed(Keyboard::Up)) {
                if (ustCarpisma(s.getPosition().x, s.getPosition().y, sinir) == 0) s.move(0, -0.1 * zaman);
                s.setTextureRect(IntRect(0, 0, 100, 100));
                durum1 = 3;
            }
            else {
                if (Keyboard::isKeyPressed(Keyboard::Down)) {
                    if (altCarpisma(s.getPosition().x, s.getPosition().y, sinir) == 0) s.move(0, 0.1 * zaman);
                    s.setTextureRect(IntRect(200, 0, 100, 100));
                    durum1 = 4;
                }
            }
        }
    }

    // Oyuncu 1'in hareketi
    if (Keyboard::isKeyPressed(Keyboard::A)) {
        if (solCarpisma(s2.getPosition().x, s2.getPosition().y, sinir) == 0) s2.move(-0.1 * zaman, 0);
        s2.setTextureRect(IntRect(300, 0, 100, 100));
        durum2 = 1;
    }
    else {
        if (Keyboard::isKeyPressed(Keyboard::D)) {
            if (sagCarpisma(s2.getPosition().x, s2.getPosition().y, sinir) == 0) s2.move(0.1 * zaman, 0);
            s2.setTextureRect(IntRect(100, 0, 100, 100));
            durum2 = 2;
        }
        else {
            if (Keyboard::isKeyPressed(Keyboard::W)) {
                if (ustCarpisma(s2.getPosition().x, s2.getPosition().y, sinir) == 0) s2.move(0, -0.1 * zaman);
                s2.setTextureRect(IntRect(0, 0, 100, 100));
                durum2 = 3;
            }
            else {
                if (Keyboard::isKeyPressed(Keyboard::S)) {
                    if (altCarpisma(s2.getPosition().x, s2.getPosition().y, sinir) == 0) s2.move(0, 0.1 * zaman);
                    s2.setTextureRect(IntRect(200, 0, 100, 100));
                    durum2 = 4;
                }
            }
        }
    }

    // Pencerenin istenildigi zaman kapatilmasi icin tus atamasi
    if (Keyboard::isKeyPressed(Keyboard::Escape)) pencere.close();

    for (it = mermiler.begin(); it != mermiler.end(); it++)
        (*it)->güncelle(zaman, s.getPosition().x, s.getPosition().y, s2.getPosition().x, s2.getPosition().y);

    // Oyuncu 1'in mermisinin carpismasinin kontrolu
    for (it = mermiler.begin(); it != mermiler.end();) {
        Mermi* m = *it;
        if (m->o1yasiyorMu == false) {
            oyuncu2Skor++;
            if (oyuncu2Skor > 4) oyunBitti = true;
            it = mermiler.erase(it);
            s.setPosition(1300, 400);   // 1. tankin başlangic pozisyonuna geri donmesi
            s2.setPosition(100, 400);   // 2. tankin başlangic pozisyonuna geri donmesi
            delete m;
        }
        else it++;
    }

    // Oyuncu 2'nin mermisinin carpismasinin kontrolu
    for (it = mermiler.begin(); it != mermiler.end();) {
        Mermi* m = *it;
        if (m->o2yasiyorMu == false) {
            oyuncu1Skor++;
            if (oyuncu1Skor > 4) oyunBitti = true;
            it = mermiler.erase(it);
            s.setPosition(1300, 400);
            s2.setPosition(100, 400);
            delete m;
        }
        else it++;
    }

    for (it = mermiler.begin(); it != mermiler.end();) {    // Kullanilan mermilerin kontrolü
        Mermi* m = *it;
        if (m->yasiyorMu == false) {
            it = mermiler.erase(it);
            delete m;
        }
        else  it++;
    }

    // Skorlari metin haline donusturur ve gunceller
    std::string scoreString = std::to_string(oyuncu1Skor);
    std::string scoreString1 = std::to_string(oyuncu2Skor);
    skorMetni.setString(scoreString);
    skorMetni1.setString(scoreString1);
    skorMetni.setPosition(862, 0);
    skorMetni1.setPosition(712, 0);
    pencere.clear();

    // Harita uzerindeki hucreler kontrol edilir
    for (int i = 0; i < boy; i++) {
        for (int j = 0; j < en; j++) {
            if (Harita[i][j] == 'H') {
                e.setPosition(j * 50, i * 50);
                pencere.draw(e);        // Haritada engel varsa "engel" goruntusu cizilir
            }
            if (Harita[i][j] == ' ') {
                z.setPosition(j * 50, i * 50);
                pencere.draw(z);        // Bos alan varsa "zemin" goruntusu cizilir
            }
        }
    }

    // Mermi goruntusu cizilir
    for (it = mermiler.begin(); it != mermiler.end(); it++) {
        (*it)->mermiCiz(pencere);
    }

    // Oyun penceresindeki tüm nesneler ekrana cizilir
    pencere.draw(s);
    pencere.draw(s2);
    pencere.draw(skorMetni);
    pencere.draw(skorMetni1);
    pencere.display();
    }

    // Oyun penceresi kapatilir
    pencere.close();

    // Sonuc ekraninin penceresinin olusturulmasi
    RenderWindow pencere2(VideoMode(1600, 900), "Sonuclar!");

    // Sonuc ekraninin acik kalmasi
    while (pencere2.isOpen()) {
        Event olay2;
        while (pencere2.pollEvent(olay2)) {
            if (olay2.type == Event::Closed)
                pencere2.close();
        }

        // Pencerenin istenildigi zaman kapatilmasi icin tus atamasi
        if (Keyboard::isKeyPressed(Keyboard::Escape)) pencere2.close();

        pencere2.clear();

        // Kazanan tankin goruntusu pencereye cizilir
        if (oyuncu1Skor > oyuncu2Skor) {
            pencere2.draw(t1kazandi);
        } else pencere2.draw(t2kazandi);
            pencere2.display();
    }

    return 0;
}




