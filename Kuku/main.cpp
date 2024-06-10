#define SDL_MAIN_HAS_CONSOLE 0

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>



const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int RECT_WIDTH = 50;
const int RECT_HEIGHT = 50;

// 游戏状态
struct GameState {
    int rectX;
    int rectY;
    int rectSpeed;
} gameState = {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 5};

SDL_Window* window;
SDL_Renderer* renderer;
bool running = true;
TTF_Font* font;
SDL_TimerID timerID;
int TimeNumber = 0;


 SDL_Texture* textureFont;

void SetNumber(int number){
     SDL_Color color = {255, 255, 255}; // 白色文本
     char text[50] = ">>";
     sprintf(&text[strlen(text)], "%d<<", number); // 将数字追加到字符串
   // const char* text = "Timer";
    SDL_Surface* surface = TTF_RenderText_Blended(font, text, color);
    if (!surface) {
        fprintf(stderr, "Could not render text: %s\n", TTF_GetError());
        TTF_CloseFont(font);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return ;
    }

    textureFont = SDL_CreateTextureFromSurface(renderer, surface);
   
     if (!textureFont) {
        fprintf(stderr, "Could not create texture: %s\n", SDL_GetError());
        SDL_FreeSurface(surface);
        TTF_CloseFont(font);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return ;
    }
     SDL_FreeSurface(surface);

}

unsigned int  timerCallback(unsigned int interval, void* param) {
    // 定时器触发时要执行的代码
    //printf("Timer callback called!\n");
    TimeNumber++;
    SetNumber(TimeNumber);

    SDL_RemoveTimer(timerID); // 先移除当前定时器
    timerID = SDL_AddTimer(interval, timerCallback, NULL); // 然
    return 0;
}
// 初始化SDL和创建窗口
bool Init() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return false;
    }

    if (TTF_Init() == -1) {
        fprintf(stderr, "Could not initialize SDL_ttf: %s\n", TTF_GetError());
        SDL_Quit();
        return false;
    }

    window = SDL_CreateWindow("Game Title中文测试", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        return false;
    }
   

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        return false;
    }


   // font = TTF_OpenFont("Res/font/song.otf", 24);
    font = TTF_OpenFont("Res/font/misaki.ttf", 24);

    if (!font) {
        fprintf(stderr, "Could not open font: %s\n", TTF_GetError());
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return false;
    }

    timerID = SDL_AddTimer(1000, timerCallback, NULL);
    if (timerID == 0) {
        std::cout << "SDL_AddTimer Error: " << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

// 事件处理函数
void HandleEvents() {
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            running = false;
        } else if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym) {
                case SDLK_LEFT:
                    gameState.rectX -= gameState.rectSpeed;
                    break;
                case SDLK_RIGHT:
                    gameState.rectX += gameState.rectSpeed;
                    break;
                case SDLK_UP:
                    gameState.rectY -= gameState.rectSpeed;
                    break;
                case SDLK_DOWN:
                    gameState.rectY += gameState.rectSpeed;
                    break;
            }
        }  
        else if (e.type == SDL_MOUSEBUTTONDOWN) {
                // 获取鼠标位置
                int x, y;
                SDL_GetMouseState(&x, &y);
                TimeNumber++;
                SetNumber(TimeNumber);
                std::cout << "Mouse clicked at position: (" << x << ", " << y << ")" << std::endl;
            }
    }
}

 SDL_Texture* textureBg;
 
void LoopBefore(){
  //背景图渲染
    SDL_Surface* loadedSurface = IMG_Load("Res/Image/doumu.jpg");
    if (!loadedSurface) {
        std::cout << "Error: Could not load image: " << IMG_GetError() << std::endl;
        return;
    }

    textureBg = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    if (textureBg == nullptr) {
            std::cerr << "Unable to create texture from surface! SDL_Error: " << SDL_GetError() << std::endl;
            return ;
        }
     // 设置纹理的透明度
    SDL_SetTextureAlphaMod(textureBg, 200); 
    SDL_FreeSurface(loadedSurface);
    SetNumber(TimeNumber);
}


void RenderStar7(){
    int curStar = TimeNumber % 7;
    int w = RECT_WIDTH;
    int h = RECT_HEIGHT;

    // if(curStar == 6)
    // return;

    //std::cout << "curStar index: (" << curStar << ")" << std::endl;
    for(int i=0; i< 7 ; i++){

        if(i == curStar){
            SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF); // 设置绘制颜色为红色
            w = RECT_WIDTH;
            h = RECT_HEIGHT;
        }else{
            SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF); // 设置绘制颜色为红色
            w = RECT_WIDTH/2;
            h = RECT_HEIGHT/2;
        }

        SDL_Rect rect = {100+i*RECT_WIDTH+i*40,250, w, h};
        
        if(i ==0){
            rect.y -= 50;
        }
        
        if(i ==1){
            rect.y -= 20;
        }

        if(i ==3){
            rect.y += 10;
        }

        if(i == 4){
            rect.x -=60;
            rect.y +=150;
        }

        if(i == 5){
            rect.x -=30;
            rect.y +=150;
        } 
        
        if(i == 6){
            rect.x -=80;
          // rect.y +=100;
        }    

        SDL_RenderFillRect(renderer, &rect); // 绘制矩形
    }
}

// 渲染函数
void Render() {
    //底色渲染
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF); // 清除屏幕为白色
    //背景纹理
    SDL_RenderCopy(renderer, textureBg, NULL, NULL);


    SDL_Rect destRect = { 350, 50, 100, 50 };
    //SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, textureFont, NULL, &destRect);

    //角色渲染
    // SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF); // 设置绘制颜色为红色
    // SDL_Rect rect = {gameState.rectX, gameState.rectY, RECT_WIDTH, RECT_HEIGHT};
    // SDL_RenderFillRect(renderer, &rect); // 绘制矩形
    
    RenderStar7();

    SDL_RenderPresent(renderer); // 显示渲染内容
}


void LoopAfter(){
     // 清理
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
     if (SDL_RemoveTimer(timerID) != 1) {
        fprintf(stderr, "SDL_RemoveTimer failed: %s\n", SDL_GetError());
    }
    SDL_Quit();
}


void Loop(){
    SDL_Event e;
    while (running) {
        HandleEvents(); // 处理事件
        Render();      // 渲染
        SDL_Delay(16); // 控制游戏循环速度
    }
}

int main(int argc, char* argv[]) {
  
    if (!Init()) {
        std::cout << "Failed to initialize!" << std::endl;
    } else {
        // 游戏主循环
       LoopBefore();
       Loop();
       LoopAfter();
    }
   
    return 0;
}

