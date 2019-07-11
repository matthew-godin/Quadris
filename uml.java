// External Abstract Classes
interface Observer {
    public void notify(Subject subject) {}
}

abstract class Subject {
    List<Observer> observers;
    public void attach() {}
    public void detach() {}
    private void notifyObservers() {}
}

// Model

enum BlockType: char {
    case "J"
    case "O"
    ...
    case EMPTY = '-1'
}

class Board {
    List<List<BlockType>> board;
    List<Block> blocks;
    
    private void attemptMoveLeft() {}
    private void attemptMoveRight() {}
    private void attemptRotateCW() {}
    private void attemptRotateCCW() {}
    private void dropToBottom() {}
    private void checkForFilledRow() {}
}

abstract class Block extends Subject {
    public void moveLeft() {}
    public void moveRight() {}
    public void moveDown() {}
    abstract void rotateCW() {}
    abstract void rotateCCW() {}
}

// View

class View implements Observer {
    
    public void notify(Subject engine) {}
}

// Controller

class Engine extends Subject implements Observer {
    int level;
    int score;
    int highScore;
    boolean isGettingRandomBlocks;
    // Main board shit
    Board board;
    // Blocks queued for entry into the board
    Queue<Block> queuedBlocks;
    Block currentBlock;

    public void interpretCommand(String input) {}
    
    private void levelUp() {}
    private void levelDown() {}
    private void processInputFile() {}
    private void restart() {}

    public void notify(Subject block) {}
}

// Owner / Factory

class Game {
    Engine e // Controller
    View v // View
    Board board // Model
    // Constructs a board and passes it to Engine
    void startGame() {
        Board = new Board()
        e = new Engine(Board)
        v = new View();

        view.attach(Engine)
    }
    
    friend ostream& operator<<(ostream&, const Board b)
}

/** 
1. User -> View (raw input) -> Calls method on Engine
2. Engine -> processes input -> Calls method on Board
3. Board () -> Updates itself -> notifies Engine
4. Engine -> Updates itself -> notifies View
5. View updates itself
*/

View (Observer) -> Engine (Subject, Observer) -> Board (Subject, Observer) -> Block (Subject)