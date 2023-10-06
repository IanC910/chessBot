package Chess.Common;

public class Rules {
    
    public static final int BOARD_WIDTH = 8;
    public static final int BOARD_HEIGHT = 8;

    public static final int MIN_RANK = 1;
    public static final int MAX_RANK = BOARD_HEIGHT;

    public static final int MIN_FILE = 1;
    public static final int MAX_FILE = BOARD_HEIGHT;

    public static final int MIN_POSITION = 1;
    public static final int MAX_POSITION = BOARD_HEIGHT * BOARD_HEIGHT;

    public static final int INVALID_POSITION = -1;

    public static boolean isPositionValid(int position) {
        return (position >= MIN_POSITION && position <= MAX_POSITION);
    }

    public static int getRank(int position) {
        if(!isPositionValid(position)) {
            return INVALID_POSITION;
        }
        return (position / BOARD_WIDTH);
    }

    public static int getFile(int position) {
        if(!isPositionValid(position)) {
            return INVALID_POSITION;
        }
        return (position % BOARD_WIDTH);
    }

    public static int getPosition(int rank, int file) {
        int position = (rank * BOARD_WIDTH + file);
        if(!isPositionValid(position)) {
            return INVALID_POSITION;
        }
        return position;
    }
}
