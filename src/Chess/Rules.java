package Chess;

public class Rules {

    public enum Colour {
        WHITE,
        BLACK
    };

    public enum PieceType {
        PAWN,
        BISHOP,
        KNIGHT,
        ROOK,
        QUEEN,
        KING
    };
    
    // Board Dimensions
    public static final int BOARD_WIDTH         = 8;
    public static final int BOARD_HEIGHT        = 8;

    public static final int MIN_RANK            = 0;
    public static final int MAX_RANK            = BOARD_HEIGHT - 1;

    public static final int MIN_FILE            = 0;
    public static final int MAX_FILE            = BOARD_HEIGHT - 1;

    public static final int MIN_POSITION        = 0;
    public static final int MAX_POSITION        = BOARD_HEIGHT * BOARD_HEIGHT - 1;

    public static final int INVALID_POSITION    = -1;


    // Starting Positions
    public static final int WHITE_START_RANK    = MIN_RANK;
    public static final int BLACK_START_RANK    = MAX_RANK;

    public static final int WHITE_FORWARD_DIR   = 1;
    public static final int BLACK_FORWARD_DIR   = -1;

    public static final int QUEEN_START_FILE    = 3;
    public static final int KING_START_FILE     = 4;

    public static final int L_BISHOP_START_FILE = 2;
    public static final int R_BISHOP_START_FILE = 5;

    public static final int L_KNIGHT_START_FILE = 1;
    public static final int R_KNIGHT_START_FILE = 6;

    public static final int L_ROOK_START_FILE   = 0;
    public static final int R_ROOK_START_FILE   = 7;




    public static boolean isPositionValid(int position) {
        return (position >= MIN_POSITION && position <= MAX_POSITION);
    }

    public static boolean isPositionValid(int rank, int file) {
        return (rank >= MIN_RANK && rank <= MAX_RANK && file >= MIN_FILE && file <= MAX_FILE);
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

    public static Board createDefaultBoard() {
        Board defaultBoard = new Board();

        // Set King and Queen
        defaultBoard.setPiece(WHITE_START_RANK, KING_START_FILE, new Piece(Colour.WHITE, PieceType.KING));
        defaultBoard.setPiece(WHITE_START_RANK, QUEEN_START_FILE, new Piece(Colour.WHITE, PieceType.QUEEN));

        defaultBoard.setPiece(BLACK_START_RANK, KING_START_FILE, new Piece(Colour.BLACK, PieceType.KING));
        defaultBoard.setPiece(BLACK_START_RANK, QUEEN_START_FILE, new Piece(Colour.BLACK, PieceType.QUEEN));

        // Set Bishops
        defaultBoard.setPiece(WHITE_START_RANK, L_BISHOP_START_FILE, new Piece(Colour.WHITE, PieceType.BISHOP));
        defaultBoard.setPiece(WHITE_START_RANK, R_BISHOP_START_FILE, new Piece(Colour.WHITE, PieceType.BISHOP));
        defaultBoard.setPiece(BLACK_START_RANK, L_BISHOP_START_FILE, new Piece(Colour.BLACK, PieceType.BISHOP));
        defaultBoard.setPiece(BLACK_START_RANK, R_BISHOP_START_FILE, new Piece(Colour.BLACK, PieceType.BISHOP));

        // Set Knights
        defaultBoard.setPiece(WHITE_START_RANK, L_KNIGHT_START_FILE, new Piece(Colour.WHITE, PieceType.KNIGHT));
        defaultBoard.setPiece(WHITE_START_RANK, R_KNIGHT_START_FILE, new Piece(Colour.WHITE, PieceType.KNIGHT));
        defaultBoard.setPiece(BLACK_START_RANK, L_KNIGHT_START_FILE, new Piece(Colour.BLACK, PieceType.KNIGHT));
        defaultBoard.setPiece(BLACK_START_RANK, R_KNIGHT_START_FILE, new Piece(Colour.BLACK, PieceType.KNIGHT));

        // Set Rooks
        defaultBoard.setPiece(WHITE_START_RANK, L_ROOK_START_FILE, new Piece(Colour.WHITE, PieceType.ROOK));
        defaultBoard.setPiece(WHITE_START_RANK, R_ROOK_START_FILE, new Piece(Colour.WHITE, PieceType.ROOK));
        defaultBoard.setPiece(BLACK_START_RANK, L_ROOK_START_FILE, new Piece(Colour.BLACK, PieceType.ROOK));
        defaultBoard.setPiece(BLACK_START_RANK, R_ROOK_START_FILE, new Piece(Colour.BLACK, PieceType.ROOK));

        // Set Pawns
        for(int file = 0; file < MAX_FILE; file++) {
            defaultBoard.setPiece(WHITE_START_RANK + WHITE_FORWARD_DIR, file, new Piece(Colour.WHITE, PieceType.PAWN));
            defaultBoard.setPiece(BLACK_START_RANK + BLACK_FORWARD_DIR, file, new Piece(Colour.WHITE, PieceType.PAWN));
        }

        return defaultBoard;
    }
}
