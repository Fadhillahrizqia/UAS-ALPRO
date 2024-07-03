#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <algorithm> // Untuk std::max

using namespace std;

class Player {
private:
    string name;
    int health;
    int defense;
    int attackDamage;
    int cooldown; // Cooldown untuk serangan khusus
    bool buffed; // Indikator apakah pemain sudah menerima buff
    int totalDamage; // Total kerusakan yang disebabkan oleh pemain
    int buffEffect; // Menyimpan efek buff saat ini
    bool doubleDamage; // Indikator apakah serangan saat ini memiliki efek double damage

public:
    Player(string n, int h, int d, int a) 
        : name(n), health(h), defense(d), attackDamage(a), cooldown(0), buffed(false), totalDamage(0), buffEffect(0), doubleDamage(false) {}

    void attack(Player &enemy) {
        int damage = rand() % attackDamage + 10; // Serangan antara 10 hingga (attackDamage + 9)

        if (buffEffect == 1) {
            damage += damage * 0.1; // Efek buff: meningkatkan kerusakan sebesar 10%
            cout << name << " memiliki buff peningkatan kerusakan sebesar 10%!" << endl;
        } else if (doubleDamage) {
            damage *= 2; // Efek buff: double damage
            cout << name << " memiliki buff double damage!" << endl;
            doubleDamage = false; // Reset efek double damage setelah digunakan
        }

        damage -= enemy.defense; // Kurangi pertahanan musuh
        damage = max(damage, 0); // Pastikan tidak negatif
        enemy.health -= damage;
        totalDamage += damage;
        cout << name << " menyerang dan menyebabkan " << damage << " kerusakan!" << endl;

        if (buffEffect == 2) {
            health += 10; // Efek buff: tambahan penyembuhan sebesar 10
            cout << name << " mendapatkan tambahan penyembuhan sebesar 10!" << endl;
            buffEffect = 0; // Reset efek buff setelah digunakan
        }

        if (cooldown > 0) {
            cooldown--;
        } else if (totalDamage >= 45) {
            // Serangan khusus
            specialAttack(enemy);
            cooldown = 3; // Set cooldown untuk serangan khusus
            totalDamage = 0; // Reset total kerusakan
        }
    }

    void specialAttack(Player &enemy) {
        // Implementasi serangan khusus berdasarkan jenis pemain
        int damage = 0;
        if (name == "Gandalf") { // Mage
            damage = (rand() % attackDamage + 10) * 1.5; // AOE attack
            cout << name << " menggunakan serangan AOE khusus dan menyebabkan " << damage << " kerusakan!" << endl;
        } else {
            damage = (rand() % attackDamage + 10) * 1.2; // Attack lebih kuat untuk lainnya
            cout << name << " menggunakan serangan khusus dan menyebabkan " << damage << " kerusakan!" << endl;
        }
        damage -= enemy.defense;
        damage = max(damage, 0);
        enemy.health -= damage;
    }

    void receiveBuff() {
        if (!buffed) {
            int buffType = rand() % 3;
            switch (buffType) {
                case 0:
                    attackDamage += attackDamage * 0.05;
                    cout << name << " menerima buff peningkatan attack damage!" << endl;
                    break;
                case 1:
                    health += health * 0.05;
                    cout << name << " menerima buff peningkatan health!" << endl;
                    break;
                case 2:
                    defense += defense * 0.05;
                    cout << name << " menerima buff peningkatan defense!" << endl;
                    break;
            }
            buffed = true;
        }
    }

    void receiveSpecialBuff() {
        int buffType = rand() % 3;
        switch (buffType) {
            case 0:
                buffEffect = 1; // Buff peningkatan kerusakan sebesar 10%
                cout << name << " menerima buff peningkatan kerusakan sebesar 10%!" << endl;
                break;
            case 1:
                health += 10; // Tambahan penyembuhan sebesar 10
                cout << name << " menerima tambahan penyembuhan sebesar 10!" << endl;
                break;
            case 2:
                doubleDamage = true; // Buff double damage
                cout << name << " menerima buff double damage!" << endl;
                break;
        }
    }

    bool isAlive() const {
        return health > 0;
    }

    int getHealth() const {
        return health;
    }

    string getName() const {
        return name;
    }

    void callAlly(Player &ally, Player &enemy) {
        if (ally.getName() == "Gandalf") {
            int healAmount = rand() % 30 + 20;
            health += healAmount;
            cout << name << " memanggil Gandalf yang menyembuhkan " << healAmount << " health!" << endl;
        } else if (ally.getName() == "Ezio") {
            int extraDamage = rand() % 20 + 10;
            int damage = rand() % attackDamage + 10 + extraDamage;
            damage -= enemy.defense;
            damage = max(damage, 0);
            enemy.health -= damage;
            cout << name << " memanggil Ezio yang menyebabkan " << extraDamage << " kerusakan tambahan!" << endl;
        } else if (ally.getName() == "Sir Galahad") {
            defense += 5;
            cout << name << " memanggil Sir Galahad yang meningkatkan defense sebesar 5!" << endl;
        } else if (ally.getName() == "Legolas") {
            attackDamage += 5;
            cout << name << " memanggil Legolas yang meningkatkan attack damage sebesar 5!" << endl;
        } else if (ally.getName() == "Conan") {
            health += 30;
            cout << name << " memanggil Conan yang menambah health sebesar 30!" << endl;
        }
    }
};

void displayCharacterOptions() {
    cout << "1. Sir Galahad (Knight) (Health: 120, Defense: 20, Attack: 25)" << endl;
    cout << "2. Legolas (Archer) (Health: 100, Defense: 15, Attack: 30)" << endl;
    cout << "3. Gandalf (Mage) (Health: 80, Defense: 10, Attack: 35)" << endl;
    cout << "4. Conan (Barbarian) (Health: 150, Defense: 25, Attack: 20)" << endl;
    cout << "5. Ezio (Assassin) (Health: 90, Defense: 5, Attack: 40)" << endl;
}

Player chooseCharacter(int choice) {
    switch (choice) {
        case 1:
            return Player("Sir Galahad", 120, 20, 25);
        case 2:
            return Player("Legolas", 100, 15, 30);
        case 3:
            return Player("Gandalf", 80, 10, 35);
        case 4:
            return Player("Conan", 150, 25, 20);
        case 5:
            return Player("Ezio", 90, 5, 40);
        default:
            cout << "Pilihan tidak valid. Menggunakan karakter default." << endl;
            return Player("Default", 100, 10, 20);
    }
}

string rockPaperScissors() {
    string choices[] = {"rock", "paper", "scissors"};
    string playerChoice, opponentChoice;

    cout << "Pilih (rock/paper/scissors): ";
    cin >> playerChoice;

    int randIndex = rand() % 3;
    opponentChoice = choices[randIndex];

    cout << "Komputer memilih: " << opponentChoice << endl;

    if (playerChoice == opponentChoice) {
        return "draw";
    } else if ((playerChoice == "rock" && opponentChoice == "scissors") ||
               (playerChoice == "paper" && opponentChoice == "rock") ||
               (playerChoice == "scissors" && opponentChoice == "paper")) {
        return "win";
    } else {
        return "lose";
    }
}

Player chooseAlly() {
    cout << "Pilih karakter bantuan:" << endl;
    displayCharacterOptions();

    int choice;
    cin >> choice;
    return chooseCharacter(choice);
}

void grantRandomBuff(Player &player) {
    if (rand() % 2 == 0) { // 50% kemungkinan
        cout << "Fitur rock-paper-scissors muncul secara acak!" << endl;
        string result = rockPaperScissors();
        if (result == "win") {
            player.receiveSpecialBuff();
        } else {
            cout << "Tidak ada buff yang didapatkan." << endl;
        }
    }
}

int main() {
    srand(time(0)); // Inisialisasi seed acak

   
    cout << "=========================================" << endl;
    cout << "       SELAMAT DATANG DI GAME BATTLE      " << endl;
    cout << "=========================================" << endl << endl;

    cout << "Pilih mode permainan:" << endl;
    cout << "1. Player 1 vs Player 2" << endl;
    cout << "2. Player 1 vs Komputer" << endl;

    int mode;
    cin >> mode;

    if (mode == 1) {
        // Mode Player 1 vs Player 2
        cout << "Silakan pilih karakter untuk Player 1: " << endl;
        displayCharacterOptions();
        int choice;
        cin >> choice;
        Player player1 = chooseCharacter(choice);

        cout << "Silakan pilih karakter untuk Player 2: " << endl;
        displayCharacterOptions();
        cin >> choice;
        Player player2 = chooseCharacter(choice);

        cout << "Pilih karakter bantuan untuk Player 1: " << endl;
        Player ally1 = chooseAlly();

        cout << "Pilih karakter bantuan untuk Player 2: " << endl;
        Player ally2 = chooseAlly();

        cout << "Game dimulai! " << player1.getName() << " vs " << player2.getName() << endl;

        while (player1.isAlive() && player2.isAlive()) {
            // Giliran Player 1
            cout << "Giliran " << player1.getName() << endl;
            cout << "1. Serang" << endl;
            cout << "2. Gunakan Bantuan" << endl;
            int action;
            cin >> action;

            if (action == 1) {
                // Serangan
                player1.attack(player2);
                cout << "Kesehatan " << player2.getName() << ": " << player2.getHealth() << endl;
                if (!player2.isAlive()) {
                    cout << player1.getName() << " memenangkan pertandingan!" << endl;
                    break;
                }
            } else if (action == 2) {
                // Gunakan bantuan
                player1.callAlly(ally1, player2);
            }

            // Munculkan fitur rock-paper-scissors secara acak
            grantRandomBuff(player1);

            // Giliran Player 2
            cout << "Giliran " << player2.getName() << endl;
            cout << "1. Serang" << endl;
            cout << "2. Gunakan Bantuan" << endl;
            cin >> action;

            if (action == 1) {
                // Serangan
                player2.attack(player1);
                cout << "Kesehatan " << player1.getName() << ": " << player1.getHealth() << endl;
                if (!player1.isAlive()) {
                    cout << player2.getName() << " memenangkan pertandingan!" << endl;
                    break;
                }
            } else if (action == 2) {
                // Gunakan bantuan
                player2.callAlly(ally2, player1);
            }

            // Munculkan fitur rock-paper-scissors secara acak
            grantRandomBuff(player2);
        }
    } else if (mode == 2) {
        // Mode Player 1 vs Komputer
        cout << "Silakan pilih karakter untuk Player 1: " << endl;
        displayCharacterOptions();
        int choice;
        cin >> choice;
        Player player1 = chooseCharacter(choice);

        // Pilih karakter bantuan untuk Player 1
        Player ally1 = chooseAlly();

        // Pilih karakter komputer untuk Player 2 secara acak
        Player player2 = chooseCharacter(rand() % 5 + 1); // Pilih secara acak dari karakter yang tersedia

        // Pilih karakter bantuan untuk Player 2
        Player ally2 = chooseAlly();

        cout << "Game dimulai! " << player1.getName() << " vs " << player2.getName() << endl;

        while (player1.isAlive() && player2.isAlive()) {
            // Giliran Player 1
            cout << "Giliran " << player1.getName() << endl;
            cout << "1. Serang" << endl;
            cout << "2. Gunakan Bantuan" << endl;
            int action;
            cin >> action;

            if (action == 1) {
                // Serangan
                player1.attack(player2);
                cout << "Kesehatan " << player2.getName() << ": " << player2.getHealth() << endl;
                if (!player2.isAlive()) {
                    cout << player1.getName() << " memenangkan pertandingan!" << endl;
                    break;
                }
            } else if (action == 2) {
                // Gunakan bantuan
                player1.callAlly(ally1, player2);
            }

            // Munculkan fitur rock-paper-scissors secara acak
            grantRandomBuff(player1);

            // Giliran Komputer (Player 2)
            if (player2.isAlive()) {
                int computerAction = rand() % 2 + 1; // Pilih aksi secara acak antara serang atau gunakan bantuan
                cout << "Giliran " << player2.getName() << endl;
                if (computerAction == 1) {
                    // Serangan
                    player2.attack(player1);
                    cout << "Kesehatan " << player1.getName() << ": " << player1.getHealth() << endl;
                    if (!player1.isAlive()) {
                        cout << player2.getName() << " memenangkan pertandingan!" << endl;
                        break;
                    }
                } else {
                    // Gunakan bantuan
                    player2.callAlly(ally2, player1);
                }

                // Munculkan fitur rock-paper-scissors secara acak
                grantRandomBuff(player2);
            }
        }
    } else {
        cout << "Mode tidak valid. Keluar dari permainan." << endl;
    }

    return 0;
}