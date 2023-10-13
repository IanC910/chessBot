package Chess;

import Chess.Pieces.Piece;
import Common.Debug;

public class Board {

    // Static Constants
    
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
    public static final int[] START_RANK        = {WHITE_START_RANK, BLACK_START_RANK};

    public static final int WHITE_FORWARD_DIR   = 1;
    public static final int BLACK_FORWARD_DIR   = -1;
    public static final int[] FORWARD_DIR       = {WHITE_FORWARD_DIR, BLACK_FORWARD_DIR};

    public static final int QUEEN_START_FILE    = 3;
    public static final int KING_START_FILE     = 4;

    public static final int L_BISHOP_START_FILE = 2;
    public static final int R_BISHOP_START_FILE = 5;

    public static final int L_KNIGHT_START_FILE = 1;
    public static final int R_KNIGHT_START_FILE = 6;

    public static final int L_ROOK_START_FILE   = 0;
    public static final int R_ROOK_START_FILE   = 7;


    
    public static Board createDefaultBoard() {
        Board defaultBoard = new Board();

        // Set Kings
        defaultBoard.setPiece(WHITE_START_RANK, KING_START_FILE, Piece.WHITE_KING);
        defaultBoard.setPiece(BLACK_START_RANK, KING_START_FILE, Piece.BLACK_KING);

        // Set Queens
        defaultBoard.setPiece(WHITE_START_RANK, QUEEN_START_FILE, Piece.WHITE_QUEEN);
        defaultBoard.setPiece(BLACK_START_RANK, QUEEN_START_FILE, Piece.BLACK_QUEEN);

        // Set Bishops
        defaultBoard.setPiece(WHITE_START_RANK, L_BISHOP_START_FILE, Piece.WHITE_BISHOP);
        defaultBoard.setPiece(WHITE_START_RANK, R_BISHOP_START_FILE, Piece.WHITE_BISHOP);
        defaultBoard.setPiece(BLACK_START_RANK, L_BISHOP_START_FILE, Piece.BLACK_BISHOP);
        defaultBoard.setPiece(BLACK_START_RANK, R_BISHOP_START_FILE, Piece.BLACK_BISHOP);

        // Set Knights
        defaultBoard.setPiece(WHITE_START_RANK, L_KNIGHT_START_FILE, Piece.WHITE_KNIGHT);
        defaultBoard.setPiece(WHITE_START_RANK, R_KNIGHT_START_FILE, Piece.WHITE_KNIGHT);
        defaultBoard.setPiece(BLACK_START_RANK, L_KNIGHT_START_FILE, Piece.BLACK_KNIGHT);
        defaultBoard.setPiece(BLACK_START_RANK, R_KNIGHT_START_FILE, Piece.BLACK_KNIGHT);

        // Set Rooks
        defaultBoard.setPiece(WHITE_START_RANK, L_ROOK_START_FILE, Piece.WHITE_ROOK);
        defaultBoard.setPiece(WHITE_START_RANK, R_ROOK_START_FILE, Piece.WHITE_ROOK);
        defaultBoard.setPiece(BLACK_START_RANK, L_ROOK_START_FILE, Piece.BLACK_ROOK);
        defaultBoard.setPiece(BLACK_START_RANK, R_ROOK_START_FILE, Piece.BLACK_ROOK);

        // Set Pawns
        for(int f = MIN_FILE; f <= MAX_FILE; f++) {
            defaultBoard.setPiece(WHITE_START_RANK + WHITE_FORWARD_DIR, f, Piece.WHITE_PAWN);
            defaultBoard.setPiece(BLACK_START_RANK + BLACK_FORWARD_DIR, f, Piece.BLACK_PAWN);
        }

        return defaultBoard;
    }

    

    // Non-Static Members

    private Piece[][] pieces;
    private Position whiteKingPosition = null;
    private Position blackKingPosition = null;

    public Board() {
        pieces = new Piece[BOARD_HEIGHT][BOARD_WIDTH];

        for(int r = MIN_RANK; r <= MAX_RANK; r++) {
            for(int f = MIN_FILE; f <= MAX_FILE; f++) {
                pieces[r][f] = Piece.NO_PIECE;
            }
        }
    }

    public Piece getPiece(int rank, int file) {
        if(!Position.isValid(rank, file)) {
            return null;
        }

        return pieces[rank][file];
    }

    public Piece getPiece(Position position) {
        return this.getPiece(position.rank, position.file);
    }

    public void setPiece(int rank, int file, Piece piece) {
        if(!Position.isValid(rank, file)) {
            Debug.fatal("Board.setPiece()", "Invalid Position");
        }
        if(piece == null) {
            Debug.fatal("Board.setPiece()", "Null piece");
        }

        if(piece.equals(Piece.WHITE_KING)) {
            whiteKingPosition = new Position(rank, file);
        }
        else if(piece.equals(Piece.BLACK_KING)) {
            blackKingPosition = new Position(rank, file);
        }

        this.pieces[rank][file] = piece;
    }

    public void setPiece(Position position, Piece piece) {
        this.setPiece(position.rank, position.file, piece);
    }

    public Position getKingPos(Piece.Colour colour) {
        if(colour == Piece.Colour.NONE) {
            Debug.warning("Board.getKingPos()", "colour == NONE");
            return null;
        }

        if(colour == Piece.Colour.WHITE) {
            return whiteKingPosition;
        }
        else {
            return blackKingPosition;
        }
    }

    // Maybe TODO: isPositionChecked(position)

    // Maybe TODO: isKingChecked(colour)

    public Board clone() {
        Board board = new Board();

        for(int r = MIN_RANK; r <= MAX_RANK; r++) {
            for(int f = MIN_FILE; f <= MAX_FILE; f++) {
                board.setPiece(r, f, this.pieces[r][f]);
            }
        }

        return board;
    }

    public String toString() {
        final String horizontalLine = "-----------------------------------------";
        
        StringBuilder sb = new StringBuilder();

        sb.append(horizontalLine);
        
        for(int rank = MAX_RANK; rank >= MIN_RANK; rank--) {

            sb.append("\n");
            sb.append("|");

            for(int file = MIN_FILE; file <= MAX_FILE; file++) {

                sb.append(" ");

                if(pieces[rank][file] != null) {
                    sb.append(pieces[rank][file].getSymbol());
                }
                else {
                    sb.append("  ");
                }

                sb.append(" |");
            }

            sb.append("\n");
            sb.append(horizontalLine);
        }

        sb.append("\n");

        return sb.toString();
    }

    public boolean equals(Board board) {

        for(int r = MIN_RANK; r <= MAX_RANK; r++) {
            for(int f = MIN_FILE; f <= MAX_FILE; f++) {
                Piece thisPiece = this.getPiece(r, f);
                Piece otherPiece = board.getPiece(r, f);

                if(!thisPiece.equals(otherPiece)) {
                    return false;
                }
            }
        }

        return true;
    }
}