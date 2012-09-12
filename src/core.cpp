/* VideoNewsGen
 *
 * <2012> Communist Party of the Russian Federation <adm@kprf.ru>
 *
 * Основной модуль. Реализация
 */

#include <stdio.h>
#include <string.h>
#include <gst/gst.h>
#include "core.hpp"

///////////////////////////////////////////////////////////////////
char ver[] = "Version: 0.1 (12/09/2012)";
/////////////////////////////////////////////////////////////////// 

int main (int argc, char **argv)
{
  GMainLoop *mainloop = NULL;
  GstElement *mainpipeline;
  GstElement *videotestsrc, *ximagesink;
  

  // Выдаем сообщение о версии программы  
  fprintf (stderr, "VideoNewsGen %s\n", ver);
  fflush  (stderr);
  
  gst_init (NULL, NULL); // Инициализируем GStreamer  
  mainloop = g_main_loop_new (NULL, TRUE); // Инициализируем цикл прослушивания сообщений
  mainpipeline = gst_pipeline_new ("mainpipeline"); // Создаем основную линию
  
  // Создаем сделующие элементы: videotestsrc и ximagesink
  //
  // Схема линии: |videotestsrc| -> |ximagesink|
  //
  videotestsrc  = gst_element_factory_make ("videotestsrc", "src"); // Элемент генерации тесового сигнала
  ximagesink    = gst_element_factory_make ("ximagesink", "out");  // Элемент вывода на X11 сервер
  // Все эти элементы из набора плагинов Base http://gstreamer.freedesktop.org/data/doc/gstreamer/head/gst-plugins-base-plugins/html/
  
  gst_bin_add_many (GST_BIN (mainpipeline), videotestsrc, ximagesink, NULL); // Добавляем на линию
  gst_element_link (videotestsrc, ximagesink); // Соединяем уже добавленные элементы вместе
  
  gst_element_set_state (GST_ELEMENT (mainpipeline), GST_STATE_PLAYING); // Запускаем линию
  
  g_main_loop_run (mainloop); // Работаем и слушаем сообщения
  g_main_loop_unref (mainloop);
  exit (EXIT_SUCCESS);
}
