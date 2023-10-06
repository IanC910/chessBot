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

    public String toString() {
        final String horizontalLine = "-----------------------------------------";
        
        StringBuilder sb = new StringBuilder();

        sb.append(horizontalLine);
        
        for(int rank = Rules.MAX_RANK; rank >= Rules.MIN_RANK; rank--) {

            sb.append("\n");
            sb.append("|");

            for(int file = Rules.MIN_FILE; file <= Rules.MAX_FILE; file++) {

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
}