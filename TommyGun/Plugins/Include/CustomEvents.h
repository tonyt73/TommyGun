/*---------------------------------------------------------------------------

    (c) 2004 Scorpio Software
        19 Wittama Drive
        Glenmore Park
        Sydney NSW 2745
        Australia

-----------------------------------------------------------------------------

    $Workfile::                                                           $
    $Revision::                                                           $
        $Date::                                                           $
      $Author::                                                           $

---------------------------------------------------------------------------*/
#ifndef __CUSTOM_EVENTS_H__
#define __CUSTOM_EVENTS_H__
//-- CUSTOM EVENTS ----------------------------------------------------------
// receives a list of the images names of a given type
#define TZXC_IMAGE_EDITOR_GET_IMAGE_NAMES       0x1001  // lpData pointer to std::vector<String>, dwParam signature of images to retrieve
// after you receive the names you can get the bitmap. The vector of bitmaps must have the correct number of allocated bitmap objects in it
#define TZXC_IMAGE_EDITOR_GET_IMAGE_BITMAPS     0x1002  // lpData pointer to std::vector<TBitmap*>, dwParam signature of images to retrieve
#define TZXC_IMAGE_EDITOR_IMAGE_CHANGED         0x1003  // lpData pointer to name of image, dwParam signature of image changed, dwArg type of operation 1 - added, 2 - removed, 3 - changed
#define TZXC_IMAGE_EDITOR_IMAGE_RENAMED         0x1004  // lpData pointer to old name of image, dwParam signature of image changed, dwArg pointer to new name of image
#define TZXC_IMAGE_EDITOR_GET_IMAGE_SUBTYPES    0x1006  // lpData pointer to std::vector<int>, dwParam signature of images to retrieve, dwArg subtype filter (-1 all or specific type)
//---------------------------------------------------------------------------
#endif // __CUSTOM_EVENTS_H__

