
#include <math.h>

void hello() {
    printf("\"hello \\/\\/orld %%d\\n\"\n");

}

void distance() {
    int x1, x2, y1, y2;
    printf("Enter x1:\n");
    scanf("%d", &x1);
    printf("Enter y1:\n");
    scanf("%d", &y1);
    printf("Enter x2:\n");
    scanf("%d", &x2);
    printf("Enter y2:\n");
    scanf("%d", &y2);
    printf("The distance between the points is: %.4f\n", sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)));
}

void conversions() {
    int nm;
    printf("Please enter nm:\n");
    scanf("%d", &nm);
    printf("%010.4f km\n%010.4f m\n%010.4f dm\n%010.4f cm\n%010.4f mm\n%010d nm\n", nm*pow(10, -12), nm*pow(10, -9), nm*pow(10, -8), nm*pow(10, -7), nm*pow(10, -6), nm);

}

void baking() {
    int bh, bm, bs, ph, pm, ps;
    printf("Please enter the baking time: [hh:mm:ss]\n");
    scanf("%d:%d:%d", &bh, &bm, &bs);
    printf("When did you put the cake into the oven? [hh:mm:ss]\n");
    scanf("%d:%d:%d", &ph, &pm, &ps);
    int rs = ps+bs, rm = pm+bm, rh = ph + bh;

    if (rs >= 60) {
        rm+=1;
        rs = rs -60;
    }
    if (rm >= 60) {
        rh+=1;
        rm = rm -60;
    }
    if (rm >= 24) {
        rh = rh - 24;
    }
    printf("The cake will be ready at %02d:%02d:%02d o'clock.", rh, rm, rs);

}

void main() {
    int n = 1;
    int a = 4;
    printf("%0ad", n);
    hello();
    distance();
    conversions();
    baking();
}



