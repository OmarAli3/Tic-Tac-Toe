#include <bits/stdc++.h>
#include<windows.h>

using namespace std;

void textcolor (int color)
{
    SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE),color);
}

class XO
{
public:
    XO()
    {
        cout<<"\t\tGame Options\n\n\tNew Game : N\tExit : X\tHigh Score : "<<score;
        cout<<"\n\nChoose Option : ";
        srand(time(NULL));
    }
    ~XO()
    {
        cout<<"\nGame ended";
    }

    void check_option()
    {
        cin>>option;
        switch(option)
        {
            {
            case 'n':
            case 'N':
            {
                system("cls");
                cout<<"\t\tGame mode\n\n\tVersus Cpu : C\tVersus Friend : F\n";
                cout<<"\n\nChoose Mode : ";
                cin>>vs;
                break;
            }
        }
        case 'x':
        case 'X':
            exit();
            break;
        default:
        {
            system("cls");
            cout<<option<<" Is Undefined Option\n";
            XO();
            check_option();
        }
        }
    }

    void check_vs()
    {
        switch(vs)
        {
        case 'c':
        case 'C':
            vs_cpu();
            break;
        case 'f':
        case 'F':
            vs_friend();
            break;
        }
    }

    void check_cell()
    {
        display();
        cout<<"Choose a Cell to play : ";
        cin>>cell;
        if(cell>='1'&&cell<='9')
        {
            r=(cell-'1')/3;
            c=(cell-'1')%3;
        }
        else
        {
            cout<<"Please choose a correct cell from 1 to 9\n";
            check_cell();
        }
    }

    void check_filled()
    {
        if(xo[r][c]=='X'||xo[r][c]=='O')
        {
            system("cls");
            switch(Mode)
            {
            case 'E':
            {
                if(turn==1)
                {
                    cout<<"You can't play in this cell\n";
                    check_cell();
                }
                else if(turn==2)easy_mode();
                break;
            }
            default:
            {
                cout<<"You can't play in this cell\n";
                check_cell();
            }
            }
        }
        else check_turn();
    }
    void display()
    {
        int i,j;
        system("cls");
        cout<<"\n";
        for(i=0; i<3; i++)
        {
            cout<<"\t";
            for(j=0; j<3; j++)
            {
                if(xo[i][j]=='X')textcolor(1);
                else if(xo[i][j]=='O')textcolor(4);
                else textcolor(7);
                cout<<xo[i][j]<<"\t";
            }

            cout<<"\n\n\n";
            textcolor(7);

        }
        switch(Mode)
        {
        case 'E':
        {
            switch(turn)
            {
            case 1:
            {
                cout<<"Your turn ( ";
                textcolor(1);
                cout<<a;
                textcolor(7);
                cout<<" -Player)\n";
                break;
            }
            case 2:
            {
                cout<<"Computer turn ( ";
                textcolor(4);
                cout<<a;
                textcolor(7);
                cout<<" -Player)\n";
                break;
            }
            }
            break;
        }
        default:
        {
            cout<<"Player "<<turn<<" turn ( ";
            textcolor(turn==1?turn:turn*2);
            cout<<a;
            textcolor(7);
            cout<<" -Player)\n";
        }
        }
    }

    void check_turn()
    {
        switch(turn)
        {
        case 1:
        {
            xo[r][c]='X';
            turn=2;
            a='O';
            ++x;
            break;
        }
        case 2:
        {
            switch(Mode)
            {
            case 'E':
            {
                display();
                cout<<"Computer Choose cell : ";
                cout<<cpu_cell<<endl;
                Sleep(1900);
                xo[r][c]='O';
                turn=1;
                a='X';
                ++o;
                break;
            }
            default :
            {
                xo[r][c]='O';
                turn=1;
                a='X';
                ++o;
            }
            }
            break;
        }
        }
    }

    void play()
    {
        check_cell();
        check_filled();
    }
private:
    char cell;
    char xo[3][3]= {{'1','2','3'},{'4','5','6'},{'7','8','9'}},a='X',option,vs,Mode=' ';
    int winner=0,turn=1,r=0,c=0,x=0,o=0,score=0;
    int cpu_cell=0;
    void exit()
    {
        system("exit");
    }

    void hard_mode()
    {
        system("cls");
        cout<<"\t\tTODO\n\n\nThis Mode is not available right now\n\n"<<endl;
    }

    void easy_mode()
    {
        if(turn==1)play();
        else
        {
            cpu_cell=rand()%9+1;
            r=(cpu_cell-1)/3;
            c=(cpu_cell-1)%3;
            check_filled();
        }
    }
    void check_difficulity()
    {
        system("cls");
        cout<<"\tGame Difficulity Mode\n\n\tHard : H\tEasy : E\n";
        cout<<"\n\nChoose Mode : ";
        char d;
        cin>>d;
        switch(d)
        {
        case 'H':
        case 'h':
            Mode='H';
            break;
        case 'e':
        case 'E':
            Mode='E';
            break;
        default:
        {
            system("cls");
            cout<<d<<" Is Undefined Mode\n";
            check_difficulity();
        }
        }

    }

    void vs_cpu()
    {
        check_difficulity();
        if(Mode=='E')
        {
            while(!winner)
            {
                if((x==4&&o==5)||(x==5&&o==4))
                {
                    winner=-1;
                    display_equality();
                    break;
                }
                switch(turn)
                {
                case 1 :
                {
                    play();
                    check_winner();
                    break;
                }
                case 2 :
                {
                    easy_mode();
                    check_winner();
                    break;
                }
                }
            }
            if(!winner) display();
        }
        else hard_mode();
    }


    void vs_friend()
    {
        while(!winner)
        {
            if((x==4&&o==5)||(x==5&&o==4))
            {
                system("cls");
                display_equality();
                break;
            }
            play();
            check_winner();
        }
    }

    void check_winner()
    {
        auto win=[](char c,char &a,int &winner)
        {
            switch(c)
            {
            case 'X':
                a='X';
                winner=1;
                break;
            case 'O':
                a='O';
                winner=2;
                break;
            }
        };

        for(int i=0; i<3; i++)
        {
            if((xo[i][0]==xo[i][1]&&xo[i][0]==xo[i][2])||(xo[0][i]==xo[1][i]&&xo[0][i]==xo[2][i]))
            {
                win(xo[i][i],a,winner);
                break;
            }
        }
        if((xo[0][0]==xo[1][1]&&xo[0][0]==xo[2][2])||(xo[0][2]==xo[1][1]&&xo[0][2]==xo[2][0]))
                win(xo[1][1],a,winner);
        if(winner)
            display_winner();
    }
    void display_equality()
    {
        int i,j;
        system("cls");
        cout<<"\n";
        for(i=0; i<3; i++)
        {
            cout<<"\t";
            for(j=0; j<3; j++)
            {
                if(xo[i][j]=='X')textcolor(1);
                else if(xo[i][j]=='O')textcolor(4);
                cout<<xo[i][j]<<"\t";
            }
            cout<<"\n\n\n";
        }
        textcolor(7);
        cout<<"End of the game (Nobody win !).\n";

    }
    void display_winner()
    {
        int i,j;
        system("cls");
        cout<<"\n";
        for(i=0; i<3; i++)
        {
            cout<<"\t";
            for(j=0; j<3; j++)
            {
                if(xo[i][j]=='X')textcolor(1);
                else if(xo[i][j]=='O')textcolor(4);
                else textcolor(7);
                cout<<xo[i][j]<<"\t";
            }
            cout<<"\n\n\n";
        }
        textcolor(7);
        if(Mode=='E')
        {
            (winner==1)?cout<<"You win !":cout<<"Computer wins !" ;
        }
        else
        {
            cout<<"Player "<<winner<<" ( ";
            textcolor(winner==1?winner:winner*2);
            cout<<a;
            textcolor(7);
            cout<<" -Player)"<<" wins\n";
        }

    }

};
