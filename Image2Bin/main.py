import sys

import cv2
import numpy as np
import os
from PySide6.QtCore import Qt, QStringListModel
from PySide6.QtGui import QKeySequence
from PySide6.QtWidgets import (QApplication, QFileDialog, QGroupBox, QListView,
                               QPushButton, QFormLayout, QMessageBox)
import struct
import sys


def BGR2Bytes(pixel):
    red = (pixel[2] >> 3) & 31
    green = (pixel[1] >> 2) & 63
    blue = (pixel[0] >> 3) & 31
    rgb = np.array([red,green,blue],dtype=np.uint16)
    newpixel = rgb[0] << 11 ^ rgb[1] << 5 ^ rgb[2]
    b = struct.pack("<H", newpixel)
    print(pixel, red, green, blue, rgb, newpixel, b)
    return b


class JanelaPrincipal(QGroupBox):

    def __init__(self, parent=None):
        super().__init__("Conversor", parent)
        self.layout = QFormLayout(self)
        self.setAlignment(Qt.AlignmentFlag.AlignCenter)
        self.setMinimumSize(800, 600)
        self.setMaximumSize(800, 600)
        self.buttonOpen = QPushButton(self)
        self.list = QListView(self)
        self.dialogOpen = QFileDialog(self)
        self.buttonSave = QPushButton(self)
        self.layout.addRow(self.buttonOpen)
        self.layout.addRow(self.list)
        self.layout.addRow(self.buttonSave)
        self.buttonO()
        self.buttonS()

    def salvarArquivos(self):
        filedir = QFileDialog.getExistingDirectory(self)
        print(filedir)
        if len(filedir)>0:
            for file in self.fileNames:
                image = cv2.imread(file)
                filename = os.path.split(file)[-1].split(".")[0]+ ".bin"
                filename = os.path.join(filedir,filename)
                with open(filename , "wb") as bin:
                    height, width, channels = image.shape
                    height = struct.pack("<H", height)
                    width = struct.pack("<H", width)
                    bin.write(height)
                    bin.write(width)
                    for line in image:
                        for pixel in line:
                            bin.write(BGR2Bytes(pixel))
                QMessageBox.warning(self,
                                    self.tr("Aviso!"),
                                    self.tr("Arquivos convertidos com sucesso!"),
                                    QMessageBox.StandardButton.Ok,
                                    QMessageBox.StandardButton.Ok)


    def abrirArquivos(self):
        filtro = self.tr("Arquivos de Imagem (*.png *.jpg *.bmp)")
        self.dialogOpen.setModal(True)
        self.dialogOpen.setNameFilter(filtro)
        self.dialogOpen.setFileMode(QFileDialog.ExistingFiles)
        self.fileNames = []
        if self.dialogOpen.exec():
            self.fileNames = self.dialogOpen.selectedFiles()
        self.slist = QStringListModel()
        self.slist.setStringList(map(lambda x: os.path.split(x)[-1], self.fileNames))
        self.list.setModel(self.slist)
        self.buttonSave.setEnabled(True)

    def buttonO(self):
        self.buttonOpen.setText(self.tr("Abrir Arquivos"))
        self.buttonOpen.setShortcut(QKeySequence.StandardKey.Open)
        self.buttonOpen.clicked.connect(self.abrirArquivos)

    def buttonS(self):
        self.buttonSave.setText(self.tr("Salvar Arquivos"))
        self.buttonSave.setShortcut(QKeySequence.StandardKey.Save)
        self.buttonSave.clicked.connect(self.salvarArquivos)
        self.buttonSave.setEnabled(False)


if __name__ == '__main__':
    app = QApplication(sys.argv)
    janela = JanelaPrincipal()
    janela.show()
    sys.exit(app.exec())
