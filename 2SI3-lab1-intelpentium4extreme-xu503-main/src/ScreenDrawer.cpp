#include "ScreenDrawer.h"
#include "MacUILib.h"

ScreenDrawer::ScreenDrawer(GameMechs* gm, Player* player, ItemBin* bin)
{
    gmRef = gm;
    playerRef = player;
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
    playerRef->drawPlayer();

    // Get the Game Board 2D array
    char** drawTarget = gmRef->getBoardRef();
    objPos target = binRef->getItem();
    
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
    MacUILib_printf("Player Score: %d\n", playerRef->getScore());
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