#ifndef MEVNI3WET2_LABELS_H
#define MEVNI3WET2_LABELS_H


class LabelBylabel {
    int label;
    int score;
public:
    LabelBylabel():label(0),score(0){};
    LabelBylabel(int label,int score): label(label),score(score){};
    void updateScore(int score1){
        score=score1;
    }

    int getLabel(){
        return label;
    }

    int getScore(){
        return score;
    }
    bool operator>(const LabelBylabel& labelBylabel){
        return (score > labelBylabel.score);
    }
    bool operator<(const LabelBylabel& labelBylabel){
        return (score < labelBylabel.score);
    }
    bool operator==(const LabelBylabel& labelBylabel){
        return (label == labelBylabel.label);
    }
    LabelBylabel& operator=(const LabelBylabel& labelBylabel){
        label=labelBylabel.label;
        score=labelBylabel.score;
        return *this;
    }
    LabelBylabel& operator+(const LabelBylabel& labelBylabel){
        label=labelBylabel.label;
        score+=labelBylabel.score;
        return *this;
    }
};


#endif //MEVNI3WET2_LABELS_H
