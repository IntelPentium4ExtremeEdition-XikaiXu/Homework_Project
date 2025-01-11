#include "ScreenDrawer.h"
#include "MacUILib.h"

ScreenDrawer::ScreenDrawer(GameMechs* gm, ItemBin* bin)
{
    gmRef = gm;
    playerRef = gmRef->getPlayerListRef();
    playerCount = gmRef->getPlayerCount();
    binRef = bin;
}

ScreenDrawer::~ScreenDrawer()
{
    // No heap member, nothing to delete here
}

void ScreenDrawer::Draw() const
{
    // Clear the Screen
    MacUILib_clearScreen();

    // redraw all items;    
    binRef->drawItem();
    for(int i = 0; i < playerCount; i++)
        playerRef[i]->drawPlayer();

    // Get the Game Board 2D array
    char** drawTarget = gmRef->getBoardRef();
    objPos target = binRef->getItem();
    
    // Lab 1 - Compute Screen Drawing Complexity

    // Draw it on the screen
    for(int i = 0; i < gmRef->getBoardSizeY(); i++)
    {
        for(int j = 0; j < gmRef->getBoardSizeX(); j++)
        {
            MacUILib_printf("%c", drawTarget[i][j]);
        }
        MacUILib_printf("\n");
    }

    // Append any required debugging message below
    for(int i = 0; i < playerCount; i++)
        MacUILib_printf("Player%d Score: %d\n", i+1, playerRef[i]->getScore());

    //MacUILib_printf("Object: <%d, %d>, ID=%c%d\n", target.getX(), target.getY(), target.getPF(), target.getNum());    
}

void ScreenDrawer::DrawEndGame() const
{
    if(gmRef->getLoseFlag())
        MacUILib_printf("You have Lost!\n");
    else
        MacUILib_printf("Game Shuts Down\n");
}

void ScreenDrawer::DrawAverageComputationTime(double data) const
{
    MacUILib_printf("Average Computation Time: %.10f ms\n", data);
}