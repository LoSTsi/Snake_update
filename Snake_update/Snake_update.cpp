#include <iostream>
#include <string>
#include <Windows.h>
#include <vector>
#include <ctime>

using threedimensional_arr = std::vector<std::vector<std::vector<int>>>;

void gotoxy(SHORT x, SHORT y)
{
    COORD pos = { x, y };
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(output, pos);
}

class  Pattern_map
{
public:
    Pattern_map()
    {
        Gen_map();
        rows_size = rows;
        cols_size = cols;
    }
    void Gen_map()
    {
        map.assign(rows, std::string(cols, '#'));

        for (int i = 1; i < rows - 1; i++)
        {
            for (int j = 1; j < cols - 1; j++)
            {
                map[i][j] = ' ';
            }
        }
        rows_size = rows;
        cols_size = cols;
    }
    void Set_Rows(int rows)
    {
        this->rows = rows;
    }
    void Set_Cols(int cols)
    {
        this->cols = cols;
    }
private:
    int rows = 40;//высота
    int cols = 110;//ширина

    int rows_size = 0;
    int cols_size = 0;

public:
    void Print()
    {
        gotoxy(0, 0);
        for (int i = 0; i < rows; i++)
        {
            std::cout << map[i];
        }
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

        // Устанавливаем размер буфера консоли (в символах)
        COORD bufferSize = { cols, rows }; // ширина, высота
        SetConsoleScreenBufferSize(hConsole, bufferSize);

        // Устанавливаем размер окна консоли (в символах)
        SMALL_RECT windowSize = { 0, 0, cols - 1, rows - 1 }; // left, top, right, bottom
        SetConsoleWindowInfo(hConsole, TRUE, &windowSize);

    }
    int Get_Rows()
    {
        return rows;
    }
    int Get_Cols()
    {
        return cols;
    }
    int Get_Rows_size()
    {
        return rows_size;
    }
    int Get_Cols_size()
    {
        return cols_size;
    }

    std::vector <std::string> map;
};

class fillings_menu//заполнения меню
{

public:
    fillings_menu(Pattern_map& other)
    {
        this->maps = &other;
        this->cols = other.Get_Cols();
        this->rows = other.Get_Rows();
    };

    void fillings_objects(std::vector<std::string>& objects, int all_objects)
    {
        accuracy_rows = 0;
        int alement = -1;
        if (all_objects % 2)
        {
            accuracy_rows++;
        }
        for (int i = (rows / 2) - (all_objects / 2); i < rows / 2 + (all_objects / 2) + accuracy_rows; i++)
        {
            alement++;
            int string_length = 0;
            accuracy_cols = 0;
            if (objects[alement].size() % 2)
            {
                accuracy_cols++;
            }

            for (int j = (cols / 2) - objects[alement].size() / 2; j < (cols / 2) + objects[alement].size() / 2 + accuracy_cols; j++)
            {
                this->maps->map[i][j] = objects[alement][string_length];
                string_length++;
            }
        }
    }

    std::vector < std::vector <int> > fillings_objects_Step_1(std::vector<std::string>& objects_Step_1, std::vector<std::string>& objects_choice, std::string& question)
    {

        std::vector < std::vector <int> > a(objects_choice.size(), std::vector <int>(0));//Масси для лови x,y  все обектов в строке  

        for (int i = 0; i < objects_choice.size(); i++)
        {
            a[i].resize(objects_choice[i].size());
        }

        fillings_objects(objects_Step_1, 1);
        for (int i = rows / 2 + 2; i < rows / 2 + 3; i++)
        {
            int begin_object = (cols / 2) - (question.size() / 2) + 2;
            int end_object = (cols / 2) + (question.size() / 2) - 2;
            int all_object_size = end_object - begin_object;
            int step_object = all_object_size / objects_choice.size();

            int current_object = 0;
            int size_current_object = 0;

            for (int j = begin_object; j < end_object; j++)
            {
                a[current_object][size_current_object] = j;
                maps->map[i][j] = objects_choice[current_object][size_current_object];

                if (size_current_object == objects_choice[current_object].size() - 1)
                {
                    size_current_object = 0;
                    current_object++;

                    if (current_object == objects_choice.size())
                    {
                        break;
                    }
                    else if (current_object == 2)
                    {
                        j += (2 * (step_object - objects_choice[current_object].size() - 1));
                    }
                    else
                    {
                        j += (step_object - objects_choice[current_object].size() - 1);
                    }

                }
                else
                {
                    size_current_object++;
                }
            }
        }
        return a;
    }

    std::vector <std::vector<int>>fillinhgs_objects_Geme_Over(std::vector<std::string>& objects_choice, std::string& question)
    {
        std::vector < std::vector <int> > a(objects_choice.size(), std::vector <int>(0));//Масси для лови x,y  все обектов в строке  

        for (int i = 0; i < objects_choice.size(); i++)
        {
            a[i].resize(objects_choice[i].size());
        }
        for (int i = rows / 2 + 2; i < rows / 2 + 3; i++)
        {
            int begin_object = (cols / 2) - (question.size() / 2) + 7;
            int end_object = (cols / 2) + (question.size() / 2) + 5;
            int all_object_size = end_object - begin_object;
            int step_object = all_object_size / objects_choice.size();

            int current_object = 0;
            int size_current_object = 0;

            for (int j = begin_object; j < end_object; j++)
            {
                a[current_object][size_current_object] = j;
                maps->map[i][j] = objects_choice[current_object][size_current_object];

                if (size_current_object == objects_choice[current_object].size() - 1)
                {
                    size_current_object = 0;
                    current_object++;

                    if (current_object == objects_choice.size())
                    {
                        break;
                    }
                    else
                    {
                        j += (step_object - objects_choice[current_object].size() - 1);
                    }

                }
                else
                {
                    size_current_object++;
                }
            }
        }
        return a;
    }

    std::vector<std::vector<std::vector<int>>> fillinhgs_objects_resize(std::vector<std::string>all_object)
    {
        threedimensional_arr rows_all_cols_all(all_object.size(), std::vector<std::vector<int>>(2, std::vector<int>(1)));

        for (int i = 0; i < all_object.size(); i++)
        {
            rows_all_cols_all[i][1].resize(all_object[i].size());
        }
        int fron_object_rows = (rows / 2) - all_object.size();
        int end_object_rows = (rows / 2) + (all_object.size() - 2);

        int all_object_sizes = 0;
        int iterator_object = 0;
        int iterator_cols_x = 0;

        int parity = 0;

        for (int rows_y = fron_object_rows; rows_y <= end_object_rows; rows_y += 2)
        {
            iterator_cols_x = 0;
            rows_all_cols_all[all_object_sizes][0][0] = rows_y;

            if (all_object[iterator_object].size() % 2 == 1)
                parity = 1;
            else
                parity = 0;

            int front_object_cols = (cols / 2) - (all_object[iterator_object].size() / 2) + parity;
            int end_object_cols = (cols / 2) + (all_object[iterator_object].size() / 2);

            for (int cols_x = front_object_cols; cols_x < end_object_cols; cols_x++)
            {
                rows_all_cols_all[all_object_sizes][1][iterator_cols_x] = cols_x;
                this->maps->map[rows_y][cols_x] = all_object[iterator_object][iterator_cols_x];

                iterator_cols_x++;
            }
            all_object_sizes++;
            iterator_object++;
        }
        return rows_all_cols_all;
    }
    std::vector<std::vector<std::vector<int>>> resize_map_size(threedimensional_arr rows_all_cols_all, std::vector<std::string>element)
    {
        int iterator_object = 0;
        int iteratoe = 0;
        int end = 0;

        threedimensional_arr rows_all_cols_all_size(element.size(), std::vector<std::vector<int>>(2, std::vector<int>(1)));

        for (int i = 0; i < element.size(); i++)
        {
            rows_all_cols_all_size[i][1].resize(element[i].size());
        }

        for (int step_y_x = 0; step_y_x < rows_all_cols_all.size(); step_y_x++)
        {
            int front_rows = rows_all_cols_all[step_y_x][0][0];

            if (step_y_x == rows_all_cols_all.size() - 1)
            {
                iteratoe = 1;
                end = 0;
            }
            else
            {
                end = 1;
                iteratoe = 0;
            }

            int end_rows = rows_all_cols_all[step_y_x + end][0][0] + iteratoe;

            int front_cols = rows_all_cols_all[step_y_x][1].back() + 5;
            int end_cols = front_cols + element[step_y_x].size();

            int iterator_element = 0;

            for (int rows_y = front_rows; rows_y < end_rows; rows_y += 2)
            {
                rows_all_cols_all_size[iterator_object][0][0] = rows_y;
                for (int cols_x = front_cols; cols_x < end_cols; cols_x++)
                {
                    rows_all_cols_all_size[iterator_object][1][iterator_element] = cols_x;
                    this->maps->map[rows_y][cols_x] = element[iterator_object][iterator_element];
                    iterator_element++;
                }
            }
            iterator_object++;
        }
        return rows_all_cols_all_size;
    }
private:
    int accuracy_rows = 0;
    int accuracy_cols = 0;
    int rows;
    int cols;
    Pattern_map* maps;

};

class Blic //Подсветка
{
public:
    Blic(Pattern_map& other)
    {
        this->maps = &other;
        this->rows = other.Get_Rows();
        this->cols = other.Get_Cols();
    };

    void blic(std::vector<std::string>& objects, int all_objects_size, int alement, bool blic_off)
    {
        if (all_objects_size % 2)
        {
            accuracy_rows++;
        }
        for (int i = (rows / 2) - (all_objects_size / 2) + alement; i < (rows / 2) + (all_objects_size / 2) + accuracy_rows; i += all_objects_size)// Строки для заполения 
        {
            accuracy_cols = 0;

            if (objects[alement].size() % 2)
            {
                accuracy_cols++;
            }

            int begin_object = (cols / 2) - (objects[alement].size() / 2);
            int end_object = (cols / 2) + (objects[alement].size() / 2) + accuracy_cols;

            int z = 0;
            if (blic_off)
            {
                for (int j = begin_object - ((backlight.size() / 2) + 1); j < end_object + ((backlight.size() / 2) + 1);)
                {

                    if (backlight.size() / 2 == 1)//Длинна при 1 занаке подсетки []
                    {
                        this->maps->map[i][j] = backlight[z];
                        j = j + objects[alement].size() + 3;
                    }
                    else//При длинне в <2 знкаов -><-
                    {
                        for (int k = 0; k < backlight.size(); k++)
                        {
                            this->maps->map[i][j] = backlight[k];

                            if ((backlight.size() / 2) == k + 1)
                            {
                                j = j + objects[alement].size() + 3;
                            }
                            else
                            {
                                j++;
                            }
                        }

                    }
                    z++;
                }
                this->maps->Print();
            }
            else
            {
                for (int j = begin_object - ((backlight.size() / 2) + 1); j < end_object + ((backlight.size() / 2) + 1);)
                {

                    if (backlight.size() / 2 == 1)//Длинна при 1 занаке подсетки []
                    {
                        this->maps->map[i][j] = ' ';
                        j = j + objects[alement].size() + 3;
                    }
                    else//При длинне в <2 знкаов -><-
                    {
                        for (int k = 0; k < backlight.size(); k++)
                        {
                            this->maps->map[i][j] = ' ';

                            if ((backlight.size() / 2) == k + 1)
                            {
                                j = j + objects[alement].size() + 3;
                            }
                            else
                            {
                                j++;
                            }
                        }

                    }
                    z++;
                }
                this->maps->Print();
            }
        }
    }
    void blic_step_1(std::vector <std::string>& objects_choice, std::vector<std::vector<int>>& begi_end_object_all, int current_object, bool blic_off)
    {
        int begin_object = begi_end_object_all[current_object][0] - (backlight.size() / 2) - 1;
        int end_object = begi_end_object_all[current_object].back() + (backlight.size() / 2);

        if (blic_off == true)
        {
            for (int i = rows / 2 + 2; i < rows / 2 + 3; i++)
            {
                int z = 0;
                for (int j = begin_object; j < end_object + backlight.size() / 2; j++)
                {
                    if (j == begin_object + (backlight.size() / 2))
                    {
                        j -= (begin_object - end_object) + 2;
                    }
                    maps->map[i][j] = backlight[z];
                    z++;
                }
            }
            maps->Print();
        }
        else
        {
            for (int i = rows / 2 + 2; i < rows / 2 + 3; i++)
            {

                for (int j = begin_object; j < end_object + backlight.size() / 2; j++)
                {
                    if (j == begin_object + (backlight.size() / 2))
                    {
                        j -= (begin_object - end_object) + 2;
                    }
                    maps->map[i][j] = ' ';

                }
            }
            maps->Print();
        }
    }
    void blic_size_cols(threedimensional_arr rows_all_cols_all, int current_object, bool blic_off)
    {


        int front_cols = rows_all_cols_all[current_object][1].front() - (backlight.size() / 2) - 1;
        int end_cols = rows_all_cols_all[current_object][1].back() + (backlight.size() / 2) + 1;
        int front_rows = rows_all_cols_all[current_object][0][0];
        int end_rows = front_rows + 1;

        if (blic_off == true)
        {
            for (int i = front_rows; i < end_rows; i++)
            {
                int z = 0;
                for (int j = front_cols; j <= end_cols;)
                {
                    if (j == front_cols + (backlight.size() / 2))
                    {
                        j -= (front_cols - end_cols) + 3;
                    }

                    this->maps->map[i][j] = backlight[z];
                    j++;
                    z++;
                }

            }

            maps->Print();
        }
        else
        {
            for (int i = front_rows; i < end_rows; i++)
            {
                int z = 0;
                for (int j = front_cols; j <= end_cols;)
                {
                    if (j == front_cols + (backlight.size() / 2))
                    {
                        j -= (front_cols - end_cols) + 3;
                    }

                    this->maps->map[i][j] = ' ';
                    j++;
                    z++;
                }

            }
            maps->Print();
        }
    }
    void blic_geme_over(std::vector<std::vector<int>>& begi_end_object_all, int current_object, bool blic_off)
    {
        int begin_object = begi_end_object_all[current_object].front() - (backlight.size() / 2) - 1;
        int end_object = begi_end_object_all[current_object].back() + (backlight.size() / 2) + 1;
        std::vector<int> rows_size;
        for (int i = 0; i < 2; i++)
        {
            rows_size.resize(2);
        }

        for (int i = 0; i < 1; i++)
        {
            rows_size[i] = (rows / 2) + 2;
            rows_size[i + 1] = (rows / 2) + 2;
        }

        if (blic_off == true)
        {
            for (int i = rows_size[current_object]; i < rows_size[current_object] + 1; i++)
            {
                int z = 0;
                for (int j = begin_object; j <= end_object;)
                {
                    if (j == begin_object + (backlight.size() / 2))
                    {
                        j -= (begin_object - end_object) + 3;
                    }

                    this->maps->map[i][j] = backlight[z];
                    j++;
                    z++;
                }

            }

            maps->Print();
        }
        else
        {
            for (int i = rows_size[current_object]; i < rows_size[current_object] + 1; i++)
            {
                int z = 0;
                for (int j = begin_object; j <= end_object;)
                {
                    if (j == begin_object + (backlight.size() / 2))
                    {
                        j -= (begin_object - end_object) + 3;
                    }

                    this->maps->map[i][j] = ' ';
                    j++;
                    z++;
                }

            }
            maps->Print();
        }
    }
private:
    int alement = 0;
    int accuracy_rows = 0;
    int accuracy_cols = 0;

    int rows;
    int cols;
    std::string backlight = "-><-";//знак
    Pattern_map* maps;

};

bool Exet_g = true;
bool pause_off = true;
bool Geme_off = true;
bool reisze_map_off = true;
bool Geme_resize_off = true;
bool Game_Over_off = true;
bool again_off = false;
int quantity_eat = 20;

class Menu
{
public:
    Menu()
    {
        all_objects.push_back(play);
        all_objects.push_back(options);
        all_objects.push_back(saving);
        all_objects.push_back(exti);
    };
    void Start()//2
    {

        fillings_menu Star(maps);
        maps.Gen_map();
        Star.fillings_objects(all_objects, all_objects_size);
        Blic Meny_blic(maps);
        Meny_blic.blic(all_objects, all_objects_size, 0, blic);

        maps.Print();
        Movement_selection(Meny_blic);
    }
    void Movement_selection(Blic& other)
    {
        double time = clock();

        while (Exet_g)
        {
            if (GetKeyState('W') & 0x8000 || GetKeyState(38) & 0x8000)
            {
                if ((clock() - time) / CLOCKS_PER_SEC >= 0.15)
                {
                    time = clock();
                    if (elment_menu != 0)
                    {
                        other.blic(all_objects, all_objects_size, elment_menu, false);
                        elment_menu--;
                    }
                    other.blic(all_objects, all_objects_size, elment_menu, true);
                }
            }
            if (GetKeyState('S') & 0x8000 || GetKeyState(40) & 0x8000)
            {
                if ((clock() - time) / CLOCKS_PER_SEC >= 0.15)
                {
                    time = clock();
                    if (elment_menu != 3)
                    {
                        other.blic(all_objects, all_objects_size, elment_menu, false);
                        elment_menu++;
                    }
                    other.blic(all_objects, all_objects_size, elment_menu, true);
                }
            }

            if ((clock() - time) / CLOCKS_PER_SEC >= 1)//Мигания []
            {
                time = clock();
                if (blic)
                {
                    other.blic(all_objects, all_objects_size, elment_menu, blic);
                    blic = false;
                }
                else
                {
                    other.blic(all_objects, all_objects_size, elment_menu, blic);
                    blic = true;
                }
            }
            if (GetKeyState(13) & 0x8000)
            {
                if ((clock() - time) / CLOCKS_PER_SEC >= 0.1)
                {
                    if (elment_menu == 0)
                    {
                        Geme_off = true;
                        Play Geme(maps);
                        Geme.Play_step_1();
                        Start();
                    }
                    else if (elment_menu == 1)
                    {

                    }
                    else if (elment_menu == 2)
                    {

                    }
                    else if (elment_menu == 3)
                    {
                        Exet_g = false;
                    }
                }
            }

        }
    }
    class map_reseize
    {
    public:
        map_reseize(Pattern_map& other)
        {
            this->p_map = &other;

            all_objects.push_back(rows);
            all_objects.push_back(cols);
            all_objects.push_back(eat_snake_str);

            rows_size = std::to_string(other.Get_Rows_size());
            cols_size = std::to_string(other.Get_Cols_size());
            eat_skane_size = std::to_string(quantity_eat);

            rows_size_int = other.Get_Rows_size();
            cols_size_int = other.Get_Cols_size();

            all_size.push_back(rows_size.size());
            all_size.push_back(cols_size.size());

            rows_cols_eat_size.resize(3);
            for (int i = 0; i < rows_size.size(); i++)
            {
                rows_cols_eat_size[0].push_back(rows_size[i]);
            }
            for (int i = 0; i < cols_size.size(); i++)
            {
                rows_cols_eat_size[1].push_back(cols_size[i]);
            }
            for (int i = 0; i < eat_skane_size.size(); i++)
            {
                rows_cols_eat_size[2].push_back(eat_skane_size[i]);
            }
        }

        void regen_map()
        {
            this->p_map->Gen_map();
            rows_all_cols_all = this->p_resize->fillinhgs_objects_resize(all_objects);
            rows_all_cols_all_size = this->p_resize->resize_map_size(rows_all_cols_all, rows_cols_eat_size);

            int rows_copi = this->p_map->Get_Rows_size();
            int cols_copi = this->p_map->Get_Cols_size();

            int even_numbered = 0;
            if (text.size() % 2 == 1)
            {
                even_numbered = 1;
            }
            int front_text = (cols_copi / 2) - (text.size() / 2);
            int end_text = (cols_copi / 2) + (text.size() / 2) + even_numbered;

            for (int i = (rows_copi / 2) + 4; i < (rows_copi / 2) + 5; i++)
            {
                int iterator = 0;
                for (int j = front_text; j < end_text; j++)
                {
                    this->p_map->map[i][j] = text[iterator];
                    iterator++;
                }
            }
        }
        void menue_resize()
        {
            this->p_map->Gen_map();

            fillings_menu resize(*p_map);
            this->p_resize = &resize;
            rows_all_cols_all = this->p_resize->fillinhgs_objects_resize(all_objects);
            rows_all_cols_all_size = this->p_resize->resize_map_size(rows_all_cols_all, rows_cols_eat_size);
            Blic blic_resize(*p_map);

            regen_map();
            blic_resize.blic_size_cols(rows_all_cols_all_size, elemetn_resize, true);

            double time = clock();

            while (reisze_map_off)
            {

                if (GetKeyState('W') & 0x8000 || GetKeyState(38) & 0x8000)
                {
                    if (((clock() - time) / CLOCKS_PER_SEC >= 0.15) && elemetn_resize != 0)
                    {
                        time = clock();
                        blic_resize.blic_size_cols(rows_all_cols_all_size, elemetn_resize, false);
                        elemetn_resize--;
                        blic_resize.blic_size_cols(rows_all_cols_all_size, elemetn_resize, true);
                    }
                }
                if (GetKeyState('S') & 0x8000 || GetKeyState(40) & 0x8000)
                {
                    if (((clock() - time) / CLOCKS_PER_SEC >= 0.15) && elemetn_resize != 2)
                    {
                        time = clock();
                        blic_resize.blic_size_cols(rows_all_cols_all_size, elemetn_resize, false);
                        elemetn_resize++;
                        blic_resize.blic_size_cols(rows_all_cols_all_size, elemetn_resize, true);
                    }
                }
                if (rows_cols_eat_size[elemetn_resize].size() != 3)//Набор цифр
                {
                    if (GetKeyState(48) & 0x8000 || GetKeyState(96) & 0x8000)
                    {
                        if ((clock() - time) / CLOCKS_PER_SEC >= 0.15)
                        {
                            if (rows_cols_eat_size[elemetn_resize][0] != '0')
                            {
                                time = clock();
                                rows_cols_eat_size[elemetn_resize].push_back('0');
                                regen_map();
                            }
                        }
                    }
                    if (GetKeyState(49) & 0x8000 || GetKeyState(97) & 0x8000)
                    {
                        if ((clock() - time) / CLOCKS_PER_SEC >= 0.15)
                        {
                            if (rows_cols_eat_size[elemetn_resize][0] != '0')
                            {
                                time = clock();
                                rows_cols_eat_size[elemetn_resize].push_back('1');
                                regen_map();
                            }
                            else
                            {
                                time = clock();
                                rows_cols_eat_size[elemetn_resize].clear();
                                rows_cols_eat_size[elemetn_resize].push_back('1');
                                regen_map();
                            }
                        }
                    }
                    if (GetKeyState(50) & 0x8000 || GetKeyState(98) & 0x8000)
                    {
                        if ((clock() - time) / CLOCKS_PER_SEC >= 0.15)
                        {
                            if (rows_cols_eat_size[elemetn_resize][0] != '0')
                            {
                                time = clock();
                                rows_cols_eat_size[elemetn_resize].push_back('2');
                                regen_map();
                            }
                            else
                            {
                                time = clock();
                                rows_cols_eat_size[elemetn_resize].clear();
                                rows_cols_eat_size[elemetn_resize].push_back('2');
                                regen_map();
                            }
                        }
                    }
                    if (GetKeyState(51) & 0x8000 || GetKeyState(99) & 0x8000)
                    {
                        if ((clock() - time) / CLOCKS_PER_SEC >= 0.15)
                        {
                            if (rows_cols_eat_size[elemetn_resize][0] != '0')
                            {
                                time = clock();
                                rows_cols_eat_size[elemetn_resize].push_back('3');
                                regen_map();
                            }
                            else
                            {
                                time = clock();
                                rows_cols_eat_size[elemetn_resize].clear();
                                rows_cols_eat_size[elemetn_resize].push_back('3');
                                regen_map();
                            }
                        }
                    }
                    if (GetKeyState(52) & 0x8000 || GetKeyState(100) & 0x8000)
                    {
                        if ((clock() - time) / CLOCKS_PER_SEC >= 0.15)
                        {
                            if (rows_cols_eat_size[elemetn_resize][0] != '0')
                            {
                                time = clock();
                                rows_cols_eat_size[elemetn_resize].push_back('4');
                                regen_map();
                            }
                            else
                            {
                                time = clock();
                                rows_cols_eat_size[elemetn_resize].clear();
                                rows_cols_eat_size[elemetn_resize].push_back('4');
                                regen_map();
                            }
                        }
                    }
                    if (GetKeyState(53) & 0x8000 || GetKeyState(101) & 0x8000)
                    {
                        if ((clock() - time) / CLOCKS_PER_SEC >= 0.15)
                        {
                            if (rows_cols_eat_size[elemetn_resize][0] != '0')
                            {
                                time = clock();
                                rows_cols_eat_size[elemetn_resize].push_back('5');
                                regen_map();
                            }
                            else
                            {
                                time = clock();
                                rows_cols_eat_size[elemetn_resize].clear();
                                rows_cols_eat_size[elemetn_resize].push_back('5');
                                regen_map();
                            }
                        }
                    }
                    if (GetKeyState(54) & 0x8000 || GetKeyState(102) & 0x8000)
                    {
                        if ((clock() - time) / CLOCKS_PER_SEC >= 0.15)
                        {
                            if (rows_cols_eat_size[elemetn_resize][0] != '0')
                            {
                                time = clock();
                                rows_cols_eat_size[elemetn_resize].push_back('6');
                                regen_map();
                            }
                            else
                            {
                                time = clock();
                                rows_cols_eat_size[elemetn_resize].clear();
                                rows_cols_eat_size[elemetn_resize].push_back('6');
                                regen_map();
                            }
                        }
                    }
                    if (GetKeyState(55) & 0x8000 || GetKeyState(103) & 0x8000)
                    {
                        if ((clock() - time) / CLOCKS_PER_SEC >= 0.15)
                        {
                            if (rows_cols_eat_size[elemetn_resize][0] != '0')
                            {
                                time = clock();
                                rows_cols_eat_size[elemetn_resize].push_back('7');
                                regen_map();
                            }
                            else
                            {
                                time = clock();
                                rows_cols_eat_size[elemetn_resize].clear();
                                rows_cols_eat_size[elemetn_resize].push_back('7');
                                regen_map();
                            }
                        }
                    }
                    if (GetKeyState(56) & 0x8000 || GetKeyState(104) & 0x8000)
                    {
                        if ((clock() - time) / CLOCKS_PER_SEC >= 0.15)
                        {
                            if (rows_cols_eat_size[elemetn_resize][0] != '0')
                            {
                                time = clock();
                                rows_cols_eat_size[elemetn_resize].push_back('8');
                                regen_map();
                            }
                            else
                            {
                                time = clock();
                                rows_cols_eat_size[elemetn_resize].clear();
                                rows_cols_eat_size[elemetn_resize].push_back('8');
                                regen_map();
                            }
                        }
                    }
                    if (GetKeyState(57) & 0x8000 || GetKeyState(105) & 0x8000)
                    {
                        if ((clock() - time) / CLOCKS_PER_SEC >= 0.15)
                        {
                            if (rows_cols_eat_size[elemetn_resize][0] != '0')
                            {
                                time = clock();
                                rows_cols_eat_size[elemetn_resize].push_back('9');
                                regen_map();
                            }
                            else
                            {
                                time = clock();
                                rows_cols_eat_size[elemetn_resize].clear();
                                rows_cols_eat_size[elemetn_resize].push_back('9');
                                regen_map();
                            }
                        }
                    }
                }
                if (GetKeyState(8) & 0x8000)
                {
                    if ((clock() - time) / CLOCKS_PER_SEC >= 0.15)
                    {
                        time = clock();
                        if (rows_cols_eat_size[elemetn_resize].size() != 1)
                        {
                            rows_cols_eat_size[elemetn_resize].pop_back();
                        }
                        else
                        {
                            rows_cols_eat_size[elemetn_resize].front() = '0';
                        }
                        regen_map();

                    }
                }
                if (GetKeyState(27) & 0x8000)
                {
                    if (((clock() - time) / CLOCKS_PER_SEC >= 0.1))
                    {
                        time = clock();
                        reisze_map_off = false;
                        Geme_resize_off = false;
                    }

                }

                if ((clock() - time) / CLOCKS_PER_SEC >= 0.65)//Блики
                {
                    time = clock();
                    rows_size_int = atoi(rows_cols_eat_size[0].c_str());
                    cols_size_int = atoi(rows_cols_eat_size[1].c_str());
                    quantity_eat = atoi(rows_cols_eat_size[2].c_str());

                    if (blic == true)
                    {
                        blic_resize.blic_size_cols(rows_all_cols_all_size, elemetn_resize, blic);
                        blic = false;
                    }
                    else
                    {
                        blic_resize.blic_size_cols(rows_all_cols_all_size, elemetn_resize, blic);
                        blic = true;
                    }
                }

                if (GetKeyState(13) & 0x8000)
                {

                    if ((clock() - time) / CLOCKS_PER_SEC >= 0.15)
                    {
                        time = clock();

                        if (rows_size_int > 50 || cols_size_int > 213)//Для больших значение
                        {
                            if (rows_size_int > 50)
                            {
                                rows_size_int = 50;
                            }
                            if (cols_size_int > 213)
                            {
                                cols_size_int = 213;
                            }
                        }
                        if (rows_size_int < 11 || cols_size_int < 60)//Для минимальных значений 
                        {
                            if (rows_size_int < 11)
                            {
                                rows_size_int = 11;
                            }
                            if (cols_size_int < 60)
                            {
                                cols_size_int = 60;
                            }
                        }
                        reisze_map_off = false;

                        this->p_map->Set_Cols(cols_size_int);
                        this->p_map->Set_Rows(rows_size_int);

                        this->p_map->Gen_map();
                        this->p_map->Print();
                    }
                }
            }
        }

    private:
        threedimensional_arr rows_all_cols_all;
        threedimensional_arr rows_all_cols_all_size;

        std::vector<std::string> all_objects;
        std::string rows = "Высота [max.50][min.11] ";
        std::string cols = "Шириана [max.213][min.60] ";
        std::string eat_snake_str = "Количесвто еды [min.1]";
        std::string text = "Для подтверждения нажмите [Enter] или [ESC] для выхода";

        std::string rows_size;
        std::string cols_size;
        std::string eat_skane_size;

        int rows_size_int = 0;
        int cols_size_int = 0;

        std::vector<int> all_size;
        std::vector<std::string>rows_cols_eat_size;

        int elemetn_resize = 0;
        bool blic = true;

        Pattern_map* p_map;
        fillings_menu* p_resize;
    private:

    };
    class Play
    {
    public:

        Play(Pattern_map& other)
        {
            other.Gen_map();
            this->p_map = &other;
            objects_Step_1.push_back(question);
            objects_Step_1.push_back(yes);
            objects_Step_1.push_back(no);
            objects_Step_1.push_back(back);

            objects_choice.push_back(yes);
            objects_choice.push_back(no);
            objects_choice.push_back(back);


        };
        void Play_step_1()
        {

            fillings_menu objects_Play(*p_map);
            std::vector < std::vector <int> > begin_end_object_all = objects_Play.fillings_objects_Step_1(objects_Step_1, objects_choice, question);
            Blic objects_Play_Blic(*p_map);

            objects_Play_Blic.blic_step_1(objects_choice, begin_end_object_all, 0, true);
            double time = clock();

            while (Geme_off)
            {
                if (GetKeyState('A') & 0x8000 || GetKeyState(37) & 0x8000)
                {
                    if ((clock() - time) / CLOCKS_PER_SEC >= 0.15)
                    {
                        if (now_object != 0)
                        {
                            time = clock();
                            objects_Play_Blic.blic_step_1(objects_choice, begin_end_object_all, now_object, false);
                            now_object--;
                            objects_Play_Blic.blic_step_1(objects_choice, begin_end_object_all, now_object, true);
                        }
                    }

                }
                if (GetKeyState('D') & 0x8000 || GetKeyState(39) & 0x8000)
                {
                    if ((clock() - time) / CLOCKS_PER_SEC >= 0.15)
                    {
                        time = clock();
                        if (now_object != objects_choice.size() - 1)
                        {
                            objects_Play_Blic.blic_step_1(objects_choice, begin_end_object_all, now_object, false);
                            now_object++;
                            objects_Play_Blic.blic_step_1(objects_choice, begin_end_object_all, now_object, true);
                        }
                    }
                }

                if ((clock() - time) / CLOCKS_PER_SEC >= 0.6)
                {
                    time = clock();
                    if (blic == true)
                    {
                        objects_Play_Blic.blic_step_1(objects_choice, begin_end_object_all, now_object, blic);
                        blic = false;
                    }
                    else
                    {
                        objects_Play_Blic.blic_step_1(objects_choice, begin_end_object_all, now_object, blic);
                        blic = true;
                    }
                }
                if (GetKeyState(13) & 0x8000)
                {
                    if ((clock() - time) / CLOCKS_PER_SEC >= 0.2)
                    {
                        again_off = true;
                        time = clock();
                        if (now_object == 0)
                        {
                            while (again_off)
                            {
                                again_off = false;

                                p_map->Set_Cols(110);
                                p_map->Set_Rows(40);
                                p_map->Gen_map();
                                system("cls");
                                Game Start_2(*p_map);
                                Start_2.geme();
                            }
                        }
                        else if (now_object == 1)
                        {
                            Geme_resize_off = true;
                            reisze_map_off = true;
                            map_reseize map_res(*p_map);
                            map_res.menue_resize();

                            if (Geme_resize_off == true)
                            {
                                while (again_off)
                                {
                                    again_off = false;
                                    system("cls");
                                    Game Start(*p_map);

                                    Start.geme();
                                }
                            }
                            else
                            {
                                this->p_map->Gen_map();
                                std::vector < std::vector <int> > begin_end_object_all = objects_Play.fillings_objects_Step_1(objects_Step_1, objects_choice, question);
                            }
                        }
                        else if (now_object == 2)
                        {

                            Geme_off = false;

                        }
                    }
                }
            }

        }


    private:
        int now_object = 0;
        bool blic = true;
        std::vector<std::string>objects_Step_1;
        std::string question = "Размер карты оставляем стандарный 110 x 40?";
        std::vector<std::string>objects_choice;
        std::string yes = "Да";
        std::string no = "Нет";
        std::string back = "Назад";

        Pattern_map* p_map;

    };
    class Game
    {
    public:
        class Pause
        {
        public:
            Pause(Pattern_map& other)
            {
                this->p_map = &other;

                this->all_object_pause.push_back(Continue);
                this->all_object_pause.push_back(Yes);
                this->all_object_pause.push_back(No);

                this->all_object_choice.push_back(Yes);
                this->all_object_choice.push_back(No);

            }
            void blic_element(int& element_blic, bool blic_off)
            {
                Blic pause_blic(*p_map);
                pause_blic.blic_step_1(all_object_choice, begin_end_object_all, element_blic, blic_off);
                p_map->Print();
            }
            void pause_start()
            {
                p_map->Gen_map();
                fillings_menu pause(*p_map);
                begin_end_object_all = pause.fillings_objects_Step_1(all_object_pause, all_object_choice, Continue);
                blic_element(element_blic, true);
                double time = clock();

                while (pause_off)
                {

                    if (GetKeyState('A') & 0x8000 || GetKeyState(37) & 0x8000)
                    {
                        if (((clock() - time) / CLOCKS_PER_SEC >= 0.1))
                        {
                            time = clock();
                            if (element_blic != 0)
                            {
                                blic_element(element_blic, false);
                                element_blic--;
                                blic_element(element_blic, true);
                            }
                        }

                    }
                    if (GetKeyState('D') & 0x8000 || GetKeyState(39) & 0x8000)
                    {
                        if (((clock() - time) / CLOCKS_PER_SEC >= 0.1))
                        {
                            time = clock();
                            if (element_blic != 1)
                            {
                                blic_element(element_blic, false);
                                element_blic++;
                                blic_element(element_blic, true);
                            }
                        }

                    }
                    if (GetKeyState(27) & 0x8000)
                    {
                        if (((clock() - time) / CLOCKS_PER_SEC >= 0.1))
                        {
                            time = clock();
                            pause_off = false;
                        }
                    }
                    if (GetKeyState(13) & 0x8000)
                    {
                        if (((clock() - time) / CLOCKS_PER_SEC >= 0.1))
                        {
                            time = clock();
                            if (element_blic == 0)
                            {
                                pause_off = false;
                            }
                            if (element_blic == 1)
                            {
                                pause_off = false;
                                Geme_off = false;
                            }
                        }
                    }
                    if ((clock() - time) / CLOCKS_PER_SEC >= 0.7)
                    {
                        time = clock();
                        if (blic_off == true)
                        {
                            blic_element(element_blic, blic_off);
                            blic_off = false;
                        }
                        else
                        {
                            blic_element(element_blic, blic_off);
                            blic_off = true;

                        }
                    }
                }
            }

        private:
            std::vector < std::vector <int> > begin_end_object_all;

            int element_blic = 0;
            bool blic_off = true;

            std::vector<std::string> all_object_pause;
            std::vector<std::string> all_object_choice;

            std::string Continue = "Пауза хотите продолжить ?";
            std::string Yes = "Да";
            std::string No = "Нет";

            Pattern_map* p_map;
        };
        class Game_Over
        {
        public:
            Game_Over(Pattern_map& other, int len_snake)
            {
                other.Gen_map();
                this->p_map = &other;
                this->cols = other.Get_Cols();
                this->rows = other.Get_Rows();
                score = std::to_string(len_snake - 1);

                text_score.insert(27, score);//добавляет счет

                objects_choice.push_back(menu);
                objects_choice.push_back(again);

                all_object.push_back(text);
                all_object.push_back(text_score);
                all_object.push_back(menu);
                all_object.push_back(again);

            }
            void Game_Over_start()
            {
                fillings_menu Game_over_text(*p_map);
                Blic Game_over_blic(*p_map);
                Game_over_text.fillings_objects(all_object, 2);
                std::vector < std::vector <int> > begin_end_object_all = Game_over_text.fillinhgs_objects_Geme_Over(objects_choice, text_score);
                Game_over_blic.blic_geme_over(begin_end_object_all, 0, true);
                double time = clock();

                while (Game_Over_off)
                {
                    if (GetKeyState('D') & 0x8000 || GetKeyState(39) & 0x8000)
                    {
                        if (elemen == 0)
                        {
                            if ((clock() - time) / CLOCKS_PER_SEC >= 0.1)
                            {
                                time = clock();
                                Game_over_blic.blic_geme_over(begin_end_object_all, elemen, false);
                                elemen = 1;
                                Game_over_blic.blic_geme_over(begin_end_object_all, elemen, true);
                            }
                        }
                    }
                    if (GetKeyState('A') & 0x8000 || GetKeyState(37) & 0x8000)
                    {
                        if (elemen == 1)
                        {
                            if ((clock() - time) / CLOCKS_PER_SEC >= 0.1)
                            {
                                time = clock();

                                Game_over_blic.blic_geme_over(begin_end_object_all, elemen, false);
                                elemen = 0;
                                Game_over_blic.blic_geme_over(begin_end_object_all, elemen, true);
                            }
                        }
                    }
                    if ((clock() - time) / CLOCKS_PER_SEC >= 0.6)
                    {
                        time = clock();
                        if (blic_off == true)
                        {
                            Game_over_blic.blic_geme_over(begin_end_object_all, elemen, blic_off);
                            blic_off = false;
                        }
                        else
                        {
                            Game_over_blic.blic_geme_over(begin_end_object_all, elemen, blic_off);
                            blic_off = true;
                        }
                        this->p_map->Print();
                    }
                    if (GetKeyState(13) & 0x8000)
                    {
                        if ((clock() - time) / CLOCKS_PER_SEC >= 0.1)
                        {
                            time = clock();
                            if (elemen == 0)
                            {
                                Game_Over_off = false;
                            }
                            if (elemen == 1)
                            {
                                Game_Over_off = false;
                                again_off = true;
                            }
                        }
                    }

                }
            }

        private:
            std::vector<std::string>objects_choice;
            std::vector<std::string>all_object;

            std::string text = "Вы проиграли";
            std::string text_score = "Количество набраных очков []";
            std::string menu = "Меню";
            std::string again = "Заново";

            std::string score;
            int elemen = 0;
            int rows;
            int cols;
            Pattern_map* p_map;
            bool blic_off = true;
        };
    public:
        Game(Pattern_map& other)
        {
            this->p_map = &other;
            p_map->Gen_map();
            this->cols = other.Get_Cols();
            this->rows = other.Get_Rows();
            map_area = (rows - 2) * (cols - 2);
        };
        void eat_spawn_start()
        {
            for (int i = 0; i < quantity_eat; i++)
            {
                eat_snake_rows.push_back(rand() % (rows - 2) + 1);
                eat_snake_cols.push_back(rand() % (cols - 2) + 1);
            }
            for (int i = 0; i < quantity_eat; i++)
            {
                p_map->map[eat_snake_rows[i]][eat_snake_cols[i]] = '*';
            }

        }
        void eat_spawn_add(int i)
        {
            eat_snake_rows[i] = (rand() % (rows - 2) + 1);
            eat_snake_cols[i] = (rand() % (cols - 2) + 1);
            p_map->map[eat_snake_rows[i]][eat_snake_cols[i]] = '*';
        }
        void increase_snake()
        {

            for (int j = 0; j < quantity_eat; j++)
            {
                if (snake_object_rows[0] == eat_snake_rows[j] && snake_object_cols[0] == eat_snake_cols[j])
                {
                    length_snek++;
                    eat_spawn_add(j);

                }
            }
            for (int i = (length_snek - 1); i >= 0; --i)
            {
                snake_object_rows[i + 1] = snake_object_rows[i];
                snake_object_cols[i + 1] = snake_object_cols[i];
            }
        }
        void mid_star()
        {
            for (int i = rows / 2; i < rows / 2 + 1; i++)
            {
                snake_object_rows.push_back(i);
                for (int j = cols / 2; j < cols / 2 + 1; j++)
                {
                    p_map->map[i][j] = ' ';
                    snake_object_cols.push_back(j);
                }
            }
        }
        void delete_snake()
        {
            for (int i = 0; i < length_snek; i++)
            {
                p_map->map[snake_object_rows[i]][snake_object_cols[i]] = ' ';
            }

        }
        void print_snake()
        {
            Print = true;
            for (int i = 0; i < length_snek; i++)
            {
                if (i == 0)
                {
                    p_map->map[snake_object_rows[i]][snake_object_cols[i]] = '0';
                }
                else
                {
                    p_map->map[snake_object_rows[i]][snake_object_cols[i]] = 'O';
                }
            }
            p_map->Print();
        }
        void movements_snak()
        {
            if (movements == Up)
            {
                snake_object_rows[0]--;
                Speed_snake = 0.3;
            }
            else if (movements == Down)
            {
                snake_object_rows[0]++;
                Speed_snake = 0.3;
            }
            else if (movements == Right)
            {
                snake_object_cols[0]++;
                Speed_snake = 0.2;
            }
            else if (movements == Left)
            {
                snake_object_cols[0]--;
                Speed_snake = 0.2;
            }
        }
        bool Geme_over()
        {
            if (snake_object_rows[0] == 0 || snake_object_cols[0] == 0 || snake_object_rows[0] == rows - 1 || snake_object_cols[0] == cols - 1)
            {
                Geme_off = false;
                return true;
            }
            for (int i = 1; i < length_snek; i++)
            {
                if (snake_object_rows[i] == snake_object_rows[0] && snake_object_cols[i] == snake_object_cols[0])
                {
                    Geme_off = false;
                    return true;
                }

            }
            return false;
        }
        void geme()
        {
            Geme_off = true;
            double time = clock();
            mid_star();
            time = clock();
            eat_spawn_start();
            snake_object_rows.resize(map_area);
            snake_object_cols.resize(map_area);

            while (Geme_off)
            {

                if (GetKeyState('W') & 0x8000 || GetKeyState(38) & 0x8000)
                {
                    if (Print == true)
                    {
                        if (movements != Down)
                        {
                            movements = Up;
                            Print = false;
                        }
                    }
                }
                else if (GetKeyState('S') & 0x8000 || GetKeyState(40) & 0x8000)
                {
                    if (Print == true)
                    {
                        if (movements != Up)
                        {
                            movements = Down;
                            Print = false;
                        }
                    }
                }
                else if (GetKeyState('A') & 0x8000 || GetKeyState(37) & 0x8000)
                {
                    if (Print == true)
                    {
                        if (movements != Right)
                        {
                            movements = Left;
                            Print = false;
                        }
                    }
                }
                else if (GetKeyState('D') & 0x8000 || GetKeyState(39) & 0x8000)
                {
                    if (Print == true)
                    {
                        if (movements != Left)
                        {
                            movements = Right;
                            Print = false;
                        }
                    }
                }

                if (GetKeyState(27) & 0x8000)
                {
                    if ((clock() - time) / CLOCKS_PER_SEC >= 0.1)
                    {
                        time = clock();

                        Pause pause(*p_map);
                        pause.pause_start();
                        pause_off = true;

                        this->p_map->Gen_map();
                        eat_spawn_start();
                    }
                }
                if ((clock() - time) / CLOCKS_PER_SEC >= Speed_snake)
                {
                    time = clock();
                    increase_snake();
                    movements_snak();
                    if (Geme_over() == true)
                    {
                        Game_Over_off = true;
                        Game_Over Over(*p_map, length_snek);
                        Over.Game_Over_start();
                        break;
                    }
                    print_snake();
                    delete_snake();
                }
            }
        }
    private:

        bool Print = true;
        double Speed_snake = 0;

        const int Up = 1;
        const int Down = 2;
        const int Left = 3;
        const int Right = 4;

        int movements = 1;
        int length_snek = 1;

        int map_area;
        int cols = 0;
        int rows = 0;

        std::vector<int> eat_snake_rows;
        std::vector<int> eat_snake_cols;

        std::vector <int> snake_object_rows;
        std::vector <int> snake_object_cols;
        Pattern_map* p_map;
    };
private:
    Pattern_map maps;
    bool blic = true;
    std::vector<std::string>all_objects;
    int all_objects_size = 4;
    int elment_menu = 0;
    std::string play = "Играть";
    std::string options = "Настройки";
    std::string saving = "Сохранения";
    std::string exti = "Закрыть";

};
int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(NULL);

    srand(time(NULL));
    setlocale(LC_ALL, "rus");
    Menu s;
    s.Start();
    return 0;
}