#include<SDL.h>
#include<SDL_ttf.h>
#include<iostream>
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#define height 500
#define width 330
#define display 180
#define font_color (SDL_Color){0,0,0,255}
#define background_colour 0xfff5f2f2
#define button_color 0xffffffff
#define button_width (width-gap*5)/4
#define button_height (height-display-gap*5)/4
#define gap 6
#define hover_color 0xffdfdfdf

using namespace std;

typedef struct{
    SDL_Rect rect_button;
    //uint32_t color;
    int is_click;
    int is_op;
    char button_val[2];
    int hover;
}Button;
typedef struct{
    char buffer[66];
    int buffer_index;
    char op;
    int is_op_present;
    char show[128];
    double ans;
}Screen;
void op_init(Screen* screen){
    screen->op='$';
}
void logic(Screen *screen,Button* button){
    if(screen->is_op_present && button[15].is_click && screen->buffer_index!=0){
        double num1 = atof(screen->buffer);
        double num2 = atof(screen->show);
        if(screen->op=='+'){
            screen->ans=num1+num2;
        }
        if(screen->op=='-'){
            screen->ans=num2-num1;
        }if(screen->op=='/'){
            screen->ans=num2/num1;
        }if(screen->op=='*'){
            screen->ans=num1*num2;
        }
        screen->buffer[0]='\0';
        sprintf(screen->buffer,"%.2f",screen->ans);
        screen->buffer_index=0;
        screen->show[0]='\0';
        screen->is_op_present=0;
    }
    

}
void buffer_store(Screen *screen, Button* button){
    for(int i=0;i<15;i++){

        /* Clear */
        if(i == 13 && button[i].is_click){
            screen->buffer_index = 0;
            screen->buffer[0] = '0';
            screen->buffer[1]='\0';
            screen->show[0] = '\0';
            screen->is_op_present=0;
            button[i].is_click = 0;
            return;
        }

        /* Operator */
        if(button[i].is_op && button[i].is_click && !screen->is_op_present ){
            strcat(screen->show, screen->buffer);

            screen->buffer_index = 0;
            screen->buffer[0] = '0';
            screen->buffer[1]='\0';

            screen->op = button[i].button_val[0];
            screen->is_op_present=1;
            button[i].is_click = 0;
            return;
        }

        /* Number */
        if(!button[i].is_op && button[i].is_click){

            screen->buffer[screen->buffer_index++] = button[i].button_val[0];
            screen->buffer[screen->buffer_index] = '\0';
            button[i].is_click = 0;
            return;
        }
    }
}

void display_screen(SDL_Surface* surface,TTF_Font* font,Screen* screen,Button* button){
    int size=strlen(screen->buffer);
    TTF_Font* font_open;

    if(size>=16){
        font_open=TTF_OpenFont("Arial.ttf",36);
    }
    else{
        font_open=TTF_OpenFont("Arial.ttf",36);
    }
    
    SDL_Surface *texture = TTF_RenderText_Blended(font_open,screen->buffer,font_color);
    SDL_Rect text_rect ={20,120,texture->w,texture->h};
    SDL_BlitSurface(texture,NULL,surface,&text_rect);
    SDL_FreeSurface(texture);
    TTF_CloseFont(font_open);
}
// void display_screen(SDL_Surface* surface, TTF_Font* font, Screen* screen)
// {
//     if(screen->buffer[0] == '\0') return;

//     int text_w, text_h;
//     TTF_SizeText(font, screen->buffer, &text_w, &text_h);

//     int max_width = width - 40;

//     SDL_Surface *texture =
//         TTF_RenderText_Blended(font, screen->buffer, font_color);

//     SDL_Rect text_rect;
//     text_rect.y = 120;
//     text_rect.w = texture->w;
//     text_rect.h = texture->h;

//     if(text_w <= max_width)
//         text_rect.x = 20;
//     else
//         text_rect.x = 20 - (text_w - max_width);

//     SDL_BlitSurface(texture, NULL, surface, &text_rect);
//     SDL_FreeSurface(texture);
// }

int hover_setter(Button *button,int mx,int my){
    return mx >= button->rect_button.x &&
           mx <= button->rect_button.x + button->rect_button.w &&
           my >= button->rect_button.y &&
           my <= button->rect_button.y + button->rect_button.h;
}
void button_init(SDL_Surface* surface,SDL_Window* window,Button *button){
    int j=0;
    for(int i=0;i<16;i++){
        button[i].is_op=0;
        if(i%4==0 && i!=0){
            j++;
        }
        button[i].rect_button={((i%4)+1)*gap+(i%4)*button_width,display+(j+1)*gap+button_height*j,button_width,button_height};
    }
    button[3].is_op=1;
    button[7].is_op=1;
    button[11].is_op=1;
    button[14].is_op=1;
}
void button_val_init(Button* button,FILE * fp){
    if (!fp) return;
    int i=0;
    int ch;
    while((ch=getc(fp))!=EOF && i<16){
        if (ch == '\n' || ch == '\r') continue;
        button[i].button_val[0]= (char)ch;  
        button[i].button_val[1] = '\0'; 
        printf("[%d] '%s'\n", i, button[i].button_val);
        i++;     
    }
}
void fill_button(SDL_Surface* surface,SDL_Window* window,Button *button){
     for(int i=0;i<16;i++){
        uint32_t colour_fill = button[i].hover==1?hover_color:button_color;
        SDL_FillRect(surface,&button[i].rect_button,colour_fill);
        //SDL_UpdateWindowSurface(window);
    }
}
void draw_text(TTF_Font* font,Button* button,SDL_Surface* surface,SDL_Window * window){
    for(int i =0;i<16;i++){
        SDL_Surface *texture = TTF_RenderText_Blended(font,button[i].button_val,font_color);
        SDL_Rect texture_rect ={button[i].rect_button.x+(button[i].rect_button.w-texture->w)/2,
            button[i].rect_button.y+(button[i].rect_button.h-texture->h)/2,texture->w,texture->h};
        SDL_BlitSurface(texture,NULL,surface,&texture_rect);
        //SDL_UpdateWindowSurface(window);
        SDL_FreeSurface(texture);
    }
}
void reset(Button* button){
    for(int i=0;i<16;i++){
        button[i].is_click=0;
    }
}



int main(){
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    SDL_Event event;
    SDL_Window *window = SDL_CreateWindow("Calculator",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,width,height,0);
    SDL_Surface *surface = SDL_GetWindowSurface(window);
    TTF_Font *font = TTF_OpenFont("Arial.ttf",20);
    if (!font) {
        printf("Font error: %s\n", TTF_GetError());
        return 1;
    }
    TTF_Font* font_screen = TTF_OpenFont("Arial.ttf",36);
    Screen screen ;
    screen.buffer_index=0;
    screen.buffer[0]='0';
    screen.buffer[1]='\0';
    screen.show[0] = '\0';
    screen.is_op_present=0;
    
    SDL_Rect rect_sample ={0,display,330,1};
    SDL_FillRect(surface,NULL,background_colour);
    SDL_FillRect(surface,&rect_sample,0);
    SDL_UpdateWindowSurface(window);
    

    FILE* fp = fopen("data.txt","r");
    if (!fp) {
        printf("FAILED TO OPEN data.txt\n");
        SDL_Delay(5000);
        return 1;
    }

    Button *button= (Button*)calloc(16,sizeof(Button));
    button_init(surface,window,button);
    // SDL_Delay(5000);
    button_val_init(button,fp);
    int is_running =1;
    while(is_running){
        int mx=0;
        int my=0;
        int click_x=0;
        int click_y=0;
        while ((SDL_PollEvent(&event)))
        {
           
            if(event.type==SDL_QUIT){
                is_running=0;
            }
            if (event.type == SDL_MOUSEMOTION  ) {
                mx = event.motion.x;
                my = event.motion.y;
            }
            else if( event.type==SDL_MOUSEBUTTONDOWN && event.button.state==SDL_PRESSED ){
                mx = 0;
                my = 0;
                click_x=event.button.x;
                click_y=event.button.y;
            }
            else if (event.type==SDL_MOUSEBUTTONUP && event.button.state==SDL_RELEASED)
            {
                mx=event.button.x;
                my=event.button.y;
            }
            
            for(int i=0;i<16;i++){
                button[i].hover=hover_setter(&button[i],mx,my);
                button[i].is_click=hover_setter(&button[i],click_x,click_y);
                //printf("%d",button[i].is_click);
            }
            
           
        }
        buffer_store(&screen,button);
        logic(&screen,button);
        SDL_FillRect(surface, NULL, background_colour);
        SDL_FillRect(surface, &rect_sample, 0);
        
        fill_button(surface,window,button);
        

        draw_text(font,button,surface,window);
        display_screen(surface,font_screen,&screen,button);
        SDL_UpdateWindowSurface(window);
        //op_init(&screen);
        SDL_Delay(16);
        //reset(button);
    }
    SDL_DestroyWindow(window);
    TTF_CloseFont(font);
    free(button);
    fclose(fp);

    TTF_Quit();
    SDL_Quit();
    return 1;
}