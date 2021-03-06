#ifndef UTILS_H
#define UTILS_H

#include "mlp.h"

using namespace std;

struct Example {
    vector<float> *positive1;
    vector<float> *positive2;
    vector<float> *negative1;
    vector<float> *negative2;
};

vector<float> readSpeakerFile (string speaker) {

    ifstream speaker_file("./data/train/"+speaker+".sv", ifstream::in);

    float value;
    vector<float> speaker_data = vector<float> ();
    while (speaker_file >> value) {
        speaker_data.push_back(value);
    }
    return speaker_data;
}

vector<float> readTestSpeakerFileScore (string speaker) {

    ifstream speaker_file("./data/test/"+speaker+".sv", ifstream::in);

    float value;
    vector<float> speaker_data = vector<float> ();
    while (speaker_file >> value) {
        speaker_data.push_back(value);
    }
    return speaker_data;
}

vector<float> readTestSpeakerFileDemo (string speaker) {

    ifstream speaker_file("../neuralnetwork/data/test/"+speaker+".sv", ifstream::in);

    float value;
    vector<float> speaker_data = vector<float> ();
    while (speaker_file >> value) {
        speaker_data.push_back(value);
    }
    return speaker_data;
}

vector<vector<vector<float>>> loadData (const string &name) {
    srand (time(NULL));
    unsigned size = 1097;
    if(name == "test") size = 275;

    ifstream file("./data/results/loader-"+name+".dat");
    string line;
    vector<vector<vector<float>>> data = vector<vector<vector<float>>> (size);
    unsigned i = 0;
    while(getline(file,line)) {
        cerr << "\r["<< i*100/size <<"%] Loading " << name << " data";
        istringstream iss(line);
        string speaker_file;
        vector<vector<float>> speaker_data = vector<vector<float>> ();
        while (iss >> speaker_file) {
            vector<float> single_file = readSpeakerFile(speaker_file);
            speaker_data.push_back(single_file);
        }
        data[i] = speaker_data;
        ++i;
    }
    cerr << endl;
    return data;
}

Example generateExample(vector<vector<vector<float>>> &data) {
    Example res;
    int speaker1 = rand() % (data.size());
    int speaker2 = rand() % (data.size());
    while (speaker1 == speaker2) {
        speaker2 = rand() % (data.size());
    }
    int file1 = rand() % (data[speaker1].size());
    res.positive1 = &(data[speaker1][file1]);
    int file2 = rand() % (data[speaker1].size());
    res.positive2 = &(data[speaker1][file2]);

    file1 = rand() % (data[speaker1].size());
    res.negative1 = &(data[speaker1][file1]);
    file2 = rand() % (data[speaker2].size());
    res.negative2 = &(data[speaker2][file2]);
    return res;
}

#endif