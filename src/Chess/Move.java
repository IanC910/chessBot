package Chess;

import Chess.Pieces.Piece;

public class Move {

    public Position startPos;
    public Position endPos;

    public Move(int startRank, int startFile, int endRank, int endFile) {
        this.startPos = new Position(startRank, startFile);
        this.endPos = new Position(endRank, endFile);
    }

    public boolean doesCheckOwnKing(Board board) {
        Board newBoard = board.clone();

        Piece piece = newBoard.getPiece(this.startPos);
        newBoard.setPiece(this.startPos, Piece.NO_PIECE);
        newBoard.setPiece(this.endPos, piece);

        // TODO: doesCheckOwnKing()




        return false;
    }
}