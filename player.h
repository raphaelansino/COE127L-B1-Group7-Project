#ifndef PLAYER_H
#define PLAYER_H


class player
{
    public:
        player();
        virtual ~player();
        void setName(std::string n);
        void setScore(int s);
        std::string getName();
        int getScore();

    protected:

    private:
    std::string name;
    int score;
};

#endif // PLAYER_H
