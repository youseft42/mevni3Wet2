#ifndef MEVNI3WET2_LABELS_H
#define MEVNI3WET2_LABELS_H


class LabelBylabel {
    int label;
    int score;
    int indexInHeap;
public:
    LabelBylabel():label(0),score(0){};
    LabelBylabel(int label,int score): label(label),score(score),indexInHeap(-1){};
    void updateScore(int score1){
        score=score1;
    }
    void updateIndexInHeap(int index){
        indexInHeap=index;
    };
    int getLabel(){
        return label;
    }
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
        return *this;
    }
    LabelBylabel& operator+(const LabelBylabel& labelBylabel){
        label=labelBylabel.label;
        score+=labelBylabel.score;
        return *this;
    }
};
class LabelByScore{
    int label;
    int score;
public:
    LabelByScore():label(0),score(0){};
    LabelByScore(int label,int score): label(label),score(score){};
    int getScore(){
        return score;
    }
    int getLabel(){
        return label;
    }
    bool operator==(const LabelByScore& labelByScore){
        return (label == labelByScore.label);
    }
    bool operator>(const LabelByScore& labelByScore){
        if(score == labelByScore.score) return (label > labelByScore.label);
        return  (score > labelByScore.score);
    }
    bool operator<(const LabelByScore& labelByScore){
        if(score == labelByScore.score) return (label < labelByScore.label);
        return (score < labelByScore.score);
    }
    LabelByScore& operator=(const LabelByScore& labelByScore){
        label=labelByScore.label;
        score=labelByScore.score;
        return *this;

    }
    LabelByScore& operator+(const LabelByScore& labelByScore){
        label=labelByScore.label;
        score+=labelByScore.score;
        return *this;
    }
};


#endif //MEVNI3WET2_LABELS_H
