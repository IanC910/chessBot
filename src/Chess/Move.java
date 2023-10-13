package Chess;

import Common.Debug;
import Chess.Pieces.Piece;
import Chess.Pieces.Queen;
import Chess.Pieces.Bishop;
import Chess.Pieces.Rook;

public class Move {

    public final Position startPos;
    public final Position endPos;
    public final Piece endPiece;

    public Move(int startRank, int startFile, Piece endPiece, int endRank, int endFile) {
        this.startPos = new Position(startRank, startFile);
        this.endPos = new Position(endRank, endFile);
        this.endPiece = endPiece;
    }

    public Move(Position startPos, Piece endPiece, Position endPos) {
        this.startPos = startPos;
        this.endPos = endPos;
        this.endPiece = endPiece;
    }


    // TODO: doesCheckOwnKing()
    // Assumes this.piece is not a king
    public boolean checksOwnKing(Board board) {
        if(this.endPiece.equals(Piece.WHITE_KING) || this.endPiece.equals(Piece.BLACK_KING)) {
            Debug.fatal("Move.checksOwnKing()", "Method not meant to be used for king moves");
        }

        // A move can only check it's own king if the piece moved was pinned
        // A piece cannot be pinned by a knight or pawn, only by queens, bishops, and rooks
        // A piece can be pinned only on horizontal, vertical, or 45 degree lines
        // A piece can be pinned only if it is the only piece between the king and an attacker on a valid pin line

        // Check if piece is initially on a valid pin line
        Piece.Colour thisColour = this.endPiece.colour;
        Position kingPos = board.getKingPos(thisColour);
        if(kingPos == null) {
            return false;
        }
        
        int startDirRank = this.startPos.rank - kingPos.rank;
        int startDirFile = this.startPos.file - kingPos.file;

        boolean isValidPinLine = 
            (Math.abs(startDirRank) == Math.abs(startDirFile)) ||
            (startDirRank == 0) ||
            (startDirFile == 0);

        if(!isValidPinLine) {
            return false;
        }

        // Check if piece ends on the same pin line
        int endDirRank = this.endPos.rank - kingPos.rank;
        int endDirFile = this.endPos.file - kingPos.file;

        // If same pin line, startDirRank / startDirFile == endDirRank / endDirFile, but account for 0s in denominator
        boolean samePinLine = 
            (startDirRank * endDirFile == endDirRank * startDirFile) && 
            (Math.signum(startDirRank) == Math.signum(endDirRank)) &&
            (Math.signum(startDirFile) == Math.signum(endDirFile));

        if(samePinLine) {
            return false;
        }

        // Simulate Move
        Board newBoard = board.clone();
        newBoard.setPiece(this.startPos, Piece.NO_PIECE);
        newBoard.setPiece(this.endPos, endPiece);

        // Check if there is no defending piece between its king and an attacker after the move
        int normalDirRank = startDirRank;
        int normalDirFile = startDirFile;

        if(normalDirRank != 0) {
            normalDirRank = normalDirRank / Math.abs(normalDirRank);
        }
        if(normalDirFile != 0) {
            normalDirFile = normalDirFile / Math.abs(normalDirFile);
        }

        int rank = kingPos.rank;
        int file = kingPos.file;

        while(true) {
            rank += normalDirRank;
            file += normalDirFile;

            Piece piece = newBoard.getPiece(rank, file);

            if(piece == null) {
                // Off the board: the pin line contains no attackers
                return false;
            }

            if(piece.equals(Piece.NO_PIECE)) {
                continue;
            }

            boolean isDefendingPiece = (piece.colour == thisColour);
            if(isDefendingPiece) {
                return false;
            }

            boolean isAttacker = 
                (piece.colour == thisColour.getOther()) &&
                (piece instanceof Queen || piece instanceof Bishop || piece instanceof Rook);

            if(isAttacker) {
                return true;
            }
        }
    }
}