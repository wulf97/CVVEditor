#include "ui_SwapFace.h"
#include "SwapFace.h"

#include <QDebug>
#include <opencv2/face.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/photo.hpp>

using namespace cv;
using namespace cv::face;
using namespace std;

SwapFace::SwapFace(QWidget *parent) :
               QWidget(parent),
               ui(new Ui::SwapFace) {
    ui->setupUi(this);
}

SwapFace::~SwapFace() {
    delete ui;
}

int SwapFace::getID() const {
    return 1;
}

QString SwapFace::getName() const {
    return "SwapFace";
}

void SwapFace::display(QBoxLayout *layout) {
    if (this->isHidden()) {
        this->show();
    }
    layout->addWidget(this);
}

void SwapFace::handle(Mat &frame) {
    CascadeClassifier faceCascade;
    Ptr<FacemarkLBF> facemark = FacemarkLBF::create();
    vector<Rect> faces;
    vector<vector<Point2f>> shapes;
    Mat buf, buf2;
    Mat gray;

    bool cascadeLoaded = faceCascade.load("../CVVEditor/plugins/SwapFace/res/haarcascade_frontalface_alt2.xml");
    if (!cascadeLoaded) {
        qDebug() << "Can not load haar cascade" << endl;
    }

    facemark->loadModel("../CVVEditor/plugins/SwapFace/res/lbfmodel.yaml");

    if (frame.channels() == 3) {
        cvtColor(frame, gray, CV_BGR2GRAY);
    }

    faceCascade.detectMultiScale(gray, faces);
    facemark->fit(frame, faces, shapes);

    vector<Mat> mask(2);
    mask[0] = Mat::zeros(frame.rows, frame.cols, frame.depth());
    mask[1] = Mat::zeros(frame.rows, frame.cols, frame.depth());
    if (faces.size() == 2) {
        vector<vector<int>>index(shapes.size());
        vector<vector<Point>> boundary(shapes.size());
        for (int i = 0; i < 2; i++) {
            convexHull(Mat(shapes[i]), index[i], false);

            for (int j = 0; j < index[i].size(); j++) {
                boundary[i].push_back(shapes[i][index[i][j]]);
            }

            fillConvexPoly(mask[i], boundary[i], Scalar(255, 255, 255));
        }

        Rect r = boundingRect(boundary[0]);

        Rect r1 = boundingRect(boundary[0]);
        Rect r2 = boundingRect(boundary[1]);
        Point center = (r.tl() + r.br()) / 2;
        Mat img = frame.clone();
        Mat a = frame.clone();
        cv::resize(a, a, Size(), (float)r1.width/r2.width,
              (float)r1.height/r2.height);
        cv::resize(mask[1], mask[1], Size(), (float)r1.width/r2.width,
              (float)r1.height/r2.height);
        seamlessClone(a, img, mask[1], center, buf, NORMAL_CLONE);
        frame = buf.clone();

        r = boundingRect(boundary[1]);
        center = (r.tl() + r.br()) / 2;

        a = img.clone();
        cv::resize(a, a, Size(), (float)r2.width/r1.width,
              (float)r2.height/r1.height);
        cv::resize(mask[0], mask[0], Size(), (float)r2.width/r1.width,
              (float)r2.height/r1.height);
        seamlessClone(a, frame, mask[0], center, buf, NORMAL_CLONE);
        frame = buf.clone();
    }

}
