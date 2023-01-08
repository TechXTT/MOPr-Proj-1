#include <iostream>

#include "line.h"
#include "field.h"

using namespace std;

int main()
{
    Point p1, p2, p3, p4;

    Line l1, l2, l3, l4;
    Field f;

    int input = 9;

    while (input != 0)
    {
        system("CLS");
        cout << "Board Complexity:\n1.Simple\n2.Complex\n(1/2):";
        cin >> input;
        switch (input)
        {
        case 1:
            cout << "Enter the first point and the size of the 2 sides(Horizontal and Vertical): ";
            float x, y, a, b;

            cin >> x >> y >> a >> b;

            p1.setPoint(x, y);
            p2.setPoint(x + a, y);
            p3.setPoint(x + a, y + b);
            p4.setPoint(x, y + b);
            try
            {
                f.setAll(p1, p2, p3, p4, true);
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << '\n';
                getchar();
                getchar();
                break;
            }

            l1.setPoints(p1, p2);
            l2.setPoints(p2, p3);
            l3.setPoints(p3, p4);
            l4.setPoints(p4, p1);

            input = 0;
            break;
        case 2:
            cout << "Enter the points of the field(x1, y1, x2, y2, x3, y3, x4, y4): ";
            float x1, y1, x2, y2, x3, y3, x4, y4;
            cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;
            p1.setPoint(x1, y1);
            p2.setPoint(x2, y2);
            p3.setPoint(x3, y3);
            p4.setPoint(x4, y4);
            try
            {
                f.setAll(p1, p2, p3, p4, false);
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << '\n';
                getchar();
                getchar();
                break;
            }
            l1.setPoints(p1, p2);
            l2.setPoints(p2, p3);
            l3.setPoints(p3, p4);
            l4.setPoints(p4, p1);

            input = 0;
            break;
        default:
            cout << "Invalid input!\n";
            getchar();
            getchar();
            break;
        }
    }

    Point ps1, ps2, ps3, ps4;
    Line ls1, ls2, ls3, ls4;
    Vector v1, v2;
    Point s, cur, end, last, oldLast;
    float diameter = 0;
    while (input != 0)
    {
        system("CLS");
        cout << "What do you want to do:\n1.Set the ball\n2.Hit the ball\n3.Show the stats\n0.Exit\n(1/2/3/0):";
        cin >> input;
        switch (input)
        {
        case 1:
            int status = 1;
            while (status)
            {
                cout << "Enter the position of the ball and diameter: ";
                float x, y, d;
                cin >> x >> y >> d;
                diameter = d;
                if (d != 0)
                {
                    Line b1(f, l4, l1, p1), b2(f, l1, l2, p2), b3(f, l2, l3, p3), b4(f, l3, l4, p4);
                    Vector vb1(b1.getVector()), vb2(b2.getVector()), vb3(b3.getVector()), vb4(b4.getVector());
                    float M = d / sqrt(2) / vb1.length();
                    ps1.setPoint(p1.x + (vb1.getX() * M), p1.y + (vb1.getY() * M));
                    ps2.setPoint(p2.x + (vb2.getX() * M), p2.y + (vb2.getY() * M));
                    ps3.setPoint(p3.x + (vb3.getX() * M), p3.y + (vb3.getY() * M));
                    ps4.setPoint(p4.x + (vb4.getX() * M), p4.y + (vb4.getY() * M));
                }
                else
                {
                    ps1 = p1;
                    ps2 = p2;
                    ps3 = p3;
                    ps4 = p4;
                }
                Field f1(ps1, ps2, ps3, ps4, false);

                s.setPoint(x, y);

                if (!f1.isInside(s))
                {
                    cout << "The ball is outside the field!\n";
                    getchar();
                    getchar();
                    status = 0;
                    continue;
                }
                ls1.setPoints(ps1, ps2);
                ls2.setPoints(ps2, ps3);
                ls3.setPoints(ps3, ps4);
                ls4.setPoints(ps4, ps1);
                v1.setPoints(ps1, ps2);
                v2.setPoints(ps1, ps4);
                status = 0;
                cur = s;
            }
            break;
        case 2:
            cout << "Enter the target point and the power(1 - 10): ";
            float x, y, p;
            Vector path;
            int bouncesEven = 0, bouncesOdd = 0;
            cin >> x >> y >> p;
            if (p < 1 || p > 10)
            {
                cout << "Invalid power!\n";
                getchar();
                getchar();
                continue;
            }
            end.setPoint(x, y);
            path.setPoints(cur, end);
            last.setPoint(cur.x + path.getX() * p, cur.y + path.getY() * p);
            oldLast = last;
            bouncesEven = f.getBouncesEven(&last, ls2, ls4, p1, v1);
            bouncesOdd = f.getBouncesOdd(&last, ls1, ls3, p1, v2);
            f.invertCheck(ls1, ls2, ls3, ls4, bouncesEven, bouncesOdd, &last);
            f.holeCheck(cur, s, path, ls1, ls2, ls3, ls4, oldLast, *last);
            cur = last;
            break;

        case 3:
            cout << "Field points:\n(" << p1.x << "," << p1.y << ")\n(" << p2.x << "," << p2.y << ")\n(" << p3.x << "," << p3.y << ")\n(" << p4.x << "," << p4.y << ")\n";
            cout << "Ball position:\n(" << cur.x << "," << cur.y << ")\n";
            cout << "Ball diameter:\n"
                 << diameter << "\n";
            getchar();
            getchar();
            break;
        case 0:
            break;

        default:
            cout << "Invalid input!\n";
            getchar();
            getchar();
            break;
        }
