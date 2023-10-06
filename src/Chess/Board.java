package Chess;

import Common.Debug;

public class Board {
    
    private Piece[][] pieces;

    public Board() {
        pieces = new Piece[Rules.BOARD_HEIGHT][Rules.BOARD_WIDTH];
        
        for(int rank = 0; rank < Rules.BOARD_HEIGHT; rank++) {
            for(int file = 0; file < Rules.BOARD_WIDTH; file++) {
                pieces[rank][file] = null;
            }

        }
    }

    public void setPiece(int rank, int file, Piece piece) {
        if(!Rules.isPositionValid(rank, file)) {
            Debug.fatal("Board.setPiece()", "Invalid Position");
        }

        pieces[rank][file] = piece;
    }

    private StringBuilder getEmptyBoardAsStringBuilder() {
        StringBuilder sb = new StringBuilder();
        
        sb.append("""
        ---------------------------------
        |   |   |   |   |   |   |   |   |
        ---------------------------------
        |   |   |   |   |   |   |   |   |
        ---------------------------------
        |   |   |   |   |   |   |   |   |
        ---------------------------------
        |   |   |   |   |   |   |   |   |
        ---------------------------------
        |   |   |   |   |   |   |   |   |
        ---------------------------------
        |   |   |   |   |   |   |   |   |
        ---------------------------------
        |   |   |   |   |   |   |   |   |
        ---------------------------------
        |   |   |   |   |   |   |   |   |
        ---------------------------------
        """);

        return sb;
    }

    public String toString() {
        StringBuilder sb = getEmptyBoardAsStringBuilder();
        
        return sb.toString();
    }
}