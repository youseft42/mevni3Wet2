#ifndef MEVNI3WET2_LABELS_H
#define MEVNI3WET2_LABELS_H


class LabelBylabel {
    int label;
    int score;
    int indexInHeap;
public:
    LabelBylabel(int label,int score): label(label),score(score),indexInHeap(-1){};
    void updateScore(int score1){
        score=score1;
    }
    void updateIndexInHeap(int index){
        indexInHeap=index;
    };
    int getIndex(){
        return indexInHeap;
    }
    int getScore(){
        return score;
    }
    bool operator>(const LabelBylabel& labelBylabel){
        return (label > labelBylabel.label);
    }
    bool operator<(const LabelBylabel& labelBylabel){
        return (label < labelBylabel.label);
    }
    bool operator==(const LabelBylabel& labelBylabel){
        return (label == labelBylabel.label);
    }
    LabelBylabel& operator=(const LabelBylabel& labelBylabel){
        label=labelBylabel.label;
        score=labelBylabel.score;
        indexInHeap=labelBylabel.indexInHeap;
    }
};
class LabelByScore{
    int label;
    int score;
public:
    LabelByScore(int label,int score): label(label),score(score){};
    int getScore(){
        return score;
    }
    bool operator==(const LabelByScore& labelByScore){
        return (label == labelByScore.label);
    }
    bool operator>(const LabelByScore& labelByScore){
        return (score > labelByScore.score);
    }
    bool operator<(const LabelByScore& labelByScore){
        return (score < labelByScore.score);
    }
    LabelByScore& operator=(const LabelByScore& labelByScore){
        label=labelByScore.label;
        score=labelByScore.score;
    }
};


#endif //MEVNI3WET2_LABELS_H
