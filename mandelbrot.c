#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <complex.h>
#include <stdbool.h>
#include <time.h>

int N = 255; //number of iteration in the set

FILE* pgmimg; //declaration of img file

complex fz(complex z,complex c) //function of mandelbrot set
{
    complex a = z*z + c;
    return(a);
}

int mandelbrotPoint(complex z, complex c)
{

    int a = 0;
    for (int i = 0; i < N; i++) //define a value between 0 and 255, 0 if it is in the set, >=1 if it is not
    {
        z = fz(z,c);
        if (cabs(z) < 4)
            a = 255-i;
        else break;
    }
    return(a);

}

int main() {
    int dim = 0;
    while (dim < 100)
    {
        printf("Enter a picture size: ");
        scanf("%d", &dim);
        if (dim < 100)
            printf("error: cannot generate a picture smaller than 100x100\n");
    }
    clock_t begin = clock();
    double points = (double) dim; //casting to a double to calculate in double value

/******************************************************************************************/
    printf("allocating space:\n");

    int **image;
    image = (int**)malloc(sizeof(int*)*dim);
    if (!image)
        printf("error: out of memory");
    for (int i = 0; i < dim; i++)
    {
        image[i] = (int*)malloc(sizeof(int)*dim);
        if (!image[i])
            printf("error: out of memory");
    }

/*****************************************************************************************/
    printf("computing picture:\n");

    for (int a = 0; a < points; a++)
    {
        for (int b = 0; b < points; b++) //calculate each pixel from top left to bottom right
        {
            double x = (a/(points/3))-2; //convert pixel position to cartesian position in mandelbrot set
            double y = (b/(points/3))-1.5;

            complex z = x + y*I; //convert x and y to complex
            complex c = 0; //define the c constant to add, 0 is the mandelbrot set. 

            image[a][b] = mandelbrotPoint(c,z);
        }
        if (a%(dim/100) == 0) printf("%d \%\n", a/(dim/100)); //show percentage done
    }

/***************************************************************************************/
    printf("generating picture\n");

    //print everything in a pgmimg file.
    pgmimg = fopen("pgmimg.pgm", "wb");

    fprintf(pgmimg, "P2\n");  
    fprintf(pgmimg, "%d %d\n", dim, dim);  
    fprintf(pgmimg, "255\n");  
    
    int count = 0; 
    
    for (int i = 0; i < dim; i++)
    { 
        for (int j = 0; j < dim; j++)
        {    
            int temp = image[i][j]; 
            fprintf(pgmimg, "%d ", temp); 

        } 
        fprintf(pgmimg, "\n"); 
    }
    fclose(pgmimg);

/***********************************************************************************/
    for (int i = 0; i < dim; i++) //free the allocated memory
        free(image[i]);
    free(image);

    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("done in %f s\n", time_spent);
}