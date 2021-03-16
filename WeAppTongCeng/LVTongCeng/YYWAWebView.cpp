/*
wx小程序同层渲染伪代码 -[YYWAWebView hitTest:withEvent:]
 */

// local variable allocation has failed, the output may be wrong!
id __cdecl -[YYWAWebView hitTest:withEvent:](YYWAWebView *self, SEL a2, CGPoint a3, id a4)
{
  double v4; // d8
  double v5; // d9
  YYWAWebView *v6; // x20
  struct objc_object *v7; // x19
  __int64 v8; // x22
  Class v9; // x23
  void *v10; // x24
  __int64 v11; // x25
  __int64 v12; // x23
  __int64 v13; // x0
  __int64 v14; // x23
  __int64 v15; // x24
  YYWAWebView *v17; // [xsp+10h] [xbp-60h]
  __objc2_class *v18; // [xsp+18h] [xbp-58h]
  CGPoint v19; // 0:d0.8,8:d1.8

  v4 = a3.var1;
  v5 = a3.var0;
  v6 = self;
  v7 = (struct objc_object *)objc_retain();
  -[YYWAWebView setIsHitSelectableText:](v6, "setIsHitSelectableText:", 0LL);
  -[YYWAWebView setIsHitTongCeng:](v6, "setIsHitTongCeng:", 0LL);
  v17 = v6;
  v18 = &OBJC_CLASS___YYWAWebView;
  objc_msgSendSuper2(&v17, "hitTest:withEvent:", v7, v5, v4);
  v8 = objc_retainAutoreleasedReturnValue();
  -[YYWAWebView setWkHitView:](v6, "setWkHitView:", v8);
  objc_release(v8);
  v9 = ((Class (__cdecl *)(WALogService_meta *, SEL))objc_msgSend)(
         (WALogService_meta *)&OBJC_CLASS___WALogService,
         "externalIMP");
  ((void (__cdecl *)(YYWAWebView *, SEL))objc_msgSend)(v6, "wkHitView");
  v10 = (void *)objc_retainAutoreleasedReturnValue();
  objc_msgSend(v10, "clsptr");
  v11 = objc_retainAutoreleasedReturnValue();
  objc_msgSend(
    v9,
    "logWithLevel:module:errorCode:file:line:func:format:",
    2LL,
    "WeApp",
    0LL,
    "YYWAWebView.mm",
    617LL,
    "-[YYWAWebView hitTest:withEvent:]",
    CFSTR("WKTongCeng wkHitView=%@"),
    v11);
  objc_release(v11);
  objc_release(v10);
  ((void (__cdecl *)(YYWAWebView *, SEL))objc_msgSend)(v6, "nativeDelegate");
  v12 = objc_retainAutoreleasedReturnValue();
  objc_release(v12);
  if ( !v12
    || (v19.var0 = v5,
        v19.var1 = v4,
        ((void (__cdecl *)(YYWAWebView *, SEL, id, CGPoint, id))objc_msgSend)(
          v6,
          "hitWKWebNativeTest:point:withEvent:",
          (id)v6,
          v19,
          v7),
        (v13 = objc_retainAutoreleasedReturnValue()) == 0) )
  {
    v15 = 0LL;
LABEL_7:
    ((void (__cdecl *)(YYWAWebView *, SEL))objc_msgSend)(v6, "wkHitView");
    v14 = objc_retainAutoreleasedReturnValue();
    objc_release(v15);
    goto LABEL_8;
  }
  v14 = v13;
  v15 = v13;
  if ( !(unsigned int)-[YYWAWebView isHitTongCeng](v6, "isHitTongCeng") )
    goto LABEL_7;
  v15 = v14;
  if ( (unsigned int)-[YYWAWebView isHitSelectableText](v6, "isHitSelectableText") )
    goto LABEL_7;
LABEL_8:
  -[YYWAWebView setWkHitView:](v6, "setWkHitView:", 0LL);
  objc_release(v7);
  return (id)objc_autoreleaseReturnValue(v14);
}


// local variable allocation has failed, the output may be wrong!
id __cdecl -[YYWAWebView hitWKWebNativeTest:point:withEvent:](YYWAWebView *self, SEL a2, id a3, CGPoint a4, id a5)
{
  double v5; // d8
  double v6; // d9
  YYWAWebView *v7; // x22
  void *v8; // x26
  struct objc_object *v9; // x27
  void *v10; // x20
  int v11; // w21
  __int64 v12; // x25
  const char *v13; // x1
  void *v14; // x19
  __int64 v15; // x20
  void *v16; // x20
  char *v17; // x23
  signed __int64 v18; // x23
  void *v19; // x25
  struct objc_object *v20; // x24
  __int64 v21; // x19
  __int64 v22; // x19
  __int64 v23; // x0
  __int64 v24; // x21
  void *v25; // x0
  void *v26; // x22
  int v27; // w23
  __int64 v28; // x1
  YYWAWebView *v29; // x26
  unsigned __int64 v30; // x24
  void *v31; // x20
  __int64 v32; // x28
  void *v33; // x0
  __int64 v34; // x22
  void *v35; // x26
  void *v36; // x19
  void *v37; // x0
  void *v38; // x26
  void *v39; // x0
  void *v40; // x0
  void *v41; // x26
  void *v42; // x0
  void *v43; // x0
  void *v44; // x20
  void *v45; // x26
  void *v46; // x0
  id result; // x0
  __int64 v48; // [xsp+0h] [xbp-1E0h]
  struct objc_object *v49; // [xsp+8h] [xbp-1D8h]
  void *v50; // [xsp+10h] [xbp-1D0h]
  void *v51; // [xsp+40h] [xbp-1A0h]
  void *v52; // [xsp+50h] [xbp-190h]
  __int64 v53; // [xsp+60h] [xbp-180h]
  __int64 v54; // [xsp+68h] [xbp-178h]
  void *v55; // [xsp+A0h] [xbp-140h]
  YYWAWebView *v56; // [xsp+A8h] [xbp-138h]
  __int128 v57; // [xsp+B0h] [xbp-130h]
  __int128 v58; // [xsp+C0h] [xbp-120h]
  __int128 v59; // [xsp+D0h] [xbp-110h]
  __int128 v60; // [xsp+E0h] [xbp-100h]
  char v61; // [xsp+F0h] [xbp-F0h]
  __int64 v62; // [xsp+170h] [xbp-70h]
  CGPoint v63; // 0:d0.8,8:d1.8

  v5 = a4.var1;
  v6 = a4.var0;
  v7 = self;
  v8 = (void *)objc_retain();
  v9 = (struct objc_object *)objc_retain();
  v56 = v7;
  if ( (unsigned int)objc_msgSend(v8, "isHidden") )
    goto LABEL_15;
  ((void (__cdecl *)(YYWAWebView *, SEL))objc_msgSend)(v7, "nativeDelegate");
  v10 = (void *)objc_retainAutoreleasedReturnValue();
  v11 = (unsigned __int64)objc_msgSend(v10, "isSelectableText:", v8);
  objc_release(v10);
  if ( v11 )
  {
    if ( (unsigned int)objc_msgSend(v8, "pointInside:withEvent:", v9, v6, v5) )
    {
      v12 = objc_retain();
      v13 = "setIsHitSelectableText:";
LABEL_8:
      objc_msgSend(v7, v13, 1LL);
      goto LABEL_16;
    }
    goto LABEL_15;
  }
  ((void (__cdecl *)(YYWAWebView *, SEL))objc_msgSend)(v7, "nativeDelegate");
  v14 = (void *)objc_retainAutoreleasedReturnValue();
  objc_msgSend(v14, "getContainerViewFromNative:", v8);
  v15 = objc_retainAutoreleasedReturnValue();
  objc_release(v15);
  objc_release(v14);
  if ( v15 )
  {
    objc_msgSend(v8, "hitTest:withEvent:", v9, v6, v5);
    v12 = objc_retainAutoreleasedReturnValue();
    if ( !v12 )
      goto LABEL_16;
    v13 = "setIsHitTongCeng:";
    goto LABEL_8;
  }
  objc_msgSend(v8, "subviews");
  v16 = (void *)objc_retainAutoreleasedReturnValue();
  v17 = (char *)objc_msgSend(v16, "count");
  objc_release(v16);
  if ( !v17 )
  {
LABEL_14:
    ((void (__cdecl *)(YYWAWebView *, SEL))objc_msgSend)(v7, "wkHitView");
    v21 = objc_retainAutoreleasedReturnValue();
    objc_release(v21);
    if ( (void *)v21 == v8 )
    {
      v12 = objc_retain();
      goto LABEL_16;
    }
LABEL_15:
    v12 = 0LL;
    goto LABEL_16;
  }
  v18 = (signed __int64)(v17 - 1);
  while ( 1 )
  {
    objc_msgSend(v8, "subviews");
    v19 = (void *)objc_retainAutoreleasedReturnValue();
    objc_msgSend(v19, "objectAtIndex:", v18);
    v20 = (struct objc_object *)objc_retainAutoreleasedReturnValue();
    objc_release(v19);
    if ( v20 )
    {
      objc_msgSend(v20, "convertPoint:fromView:", v8, v6, v5);
      ((void (__cdecl *)(YYWAWebView *, SEL, id, CGPoint, id))objc_msgSend)(
        v7,
        "hitWKWebNativeTest:point:withEvent:",
        v20,
        v63,
        v9);
      v12 = objc_retainAutoreleasedReturnValue();
      objc_release(v20);
      if ( v12 )
        break;
    }
    if ( --v18 == -1 )
      goto LABEL_14;
  }
LABEL_16:
  objc_msgSend(v8, "superview");
  v22 = objc_retainAutoreleasedReturnValue();
  objc_msgSend(v7, "scrollView");
  v23 = objc_retainAutoreleasedReturnValue();
  v24 = v23;
  if ( v22 == v23 )
  {
    v25 = objc_msgSend(v8, "class");
    NSStringFromClass(v25);
    v26 = (void *)objc_retainAutoreleasedReturnValue();
    v27 = (unsigned __int64)objc_msgSend(v26, "isEqualToString:", CFSTR("WKContentView"));
    objc_release(v26);
    objc_release(v24);
    objc_release(v22);
    if ( v27 )
    {
      v54 = NSClassFromString(CFSTR("UITapAndAHalfRecognizer"), v28);
      v51 = objc_msgSend(&OBJC_CLASS___UILongPressGestureRecognizer, "class", v12, v9);
      v57 = 0u;
      v58 = 0u;
      v59 = 0u;
      v60 = 0u;
      v50 = v8;
      objc_msgSend(v8, "gestureRecognizers");
      v52 = (void *)objc_retainAutoreleasedReturnValue();
      v29 = v56;
      v55 = objc_msgSend(v52, "countByEnumeratingWithState:objects:count:", &v57, &v61, 16LL);
      if ( v55 )
      {
        v53 = *(_QWORD *)v58;
        do
        {
          v30 = 0LL;
          do
          {
            if ( *(_QWORD *)v58 != v53 )
              objc_enumerationMutation(v52);
            v31 = *(void **)(*((_QWORD *)&v57 + 1) + 8 * v30);
            objc_msgSend(*(void **)(*((_QWORD *)&v57 + 1) + 8 * v30), "setCancelsTouchesInView:", 0LL);
            objc_msgSend(v31, "setDelaysTouchesBegan:", 0LL);
            objc_msgSend(v31, "setDelaysTouchesEnded:", 0LL);
            objc_msgSend(&OBJC_CLASS___NSValue, "valueWithNonretainedObject:", v31);
            v32 = objc_retainAutoreleasedReturnValue();
            v33 = objc_msgSend(v31, "isEnabled");
            objc_msgSend(&OBJC_CLASS___NSNumber, "numberWithBool:", v33);
            v34 = objc_retainAutoreleasedReturnValue();
            ((void (__cdecl *)(YYWAWebView *, SEL))objc_msgSend)(v29, "gestureEnableDic");
            v35 = (void *)objc_retainAutoreleasedReturnValue();
            objc_msgSend(v35, "objectForKey:", v32);
            v36 = (void *)objc_retainAutoreleasedReturnValue();
            v37 = v35;
            v29 = v56;
            objc_release(v37);
            if ( (unsigned int)objc_msgSend(v31, "isKindOfClass:", v54) )
            {
              if ( (unsigned int)-[YYWAWebView isHitTongCeng](v56, "isHitTongCeng") )
              {
                if ( !v36 )
                {
                  ((void (__cdecl *)(YYWAWebView *, SEL))objc_msgSend)(v56, "gestureEnableDic");
                  v38 = (void *)objc_retainAutoreleasedReturnValue();
                  objc_msgSend(v38, "setObject:forKey:", v34, v32);
                  v39 = v38;
                  v29 = v56;
                  objc_release(v39);
                }
                objc_msgSend(v31, "setEnabled:", 0LL);
              }
              else if ( v36 )
              {
                v40 = objc_msgSend(v36, "boolValue");
                objc_msgSend(v31, "setEnabled:", v40);
                ((void (__cdecl *)(YYWAWebView *, SEL))objc_msgSend)(v56, "gestureEnableDic");
                v41 = (void *)objc_retainAutoreleasedReturnValue();
                objc_msgSend(v41, "removeObjectForKey:", v32);
                v42 = v41;
                v29 = v56;
                objc_release(v42);
              }
            }
            if ( (unsigned int)+[DeviceInfo isiOS11plus](&OBJC_CLASS___DeviceInfo, "isiOS11plus")
              && (unsigned int)objc_msgSend(v31, "isKindOfClass:", v51) )
            {
              if ( (unsigned int)-[YYWAWebView isHitSelectableText](v29, "isHitSelectableText") )
              {
                if ( v36 )
                {
                  v43 = objc_msgSend(v36, "boolValue");
                  objc_msgSend(v31, "setEnabled:", v43);
                  ((void (__cdecl *)(YYWAWebView *, SEL))objc_msgSend)(v29, "gestureEnableDic");
                  v44 = (void *)objc_retainAutoreleasedReturnValue();
                  objc_msgSend(v44, "removeObjectForKey:", v32);
                  objc_release(v44);
                }
              }
              else
              {
                if ( !v36 )
                {
                  ((void (__cdecl *)(YYWAWebView *, SEL))objc_msgSend)(v29, "gestureEnableDic");
                  v45 = (void *)objc_retainAutoreleasedReturnValue();
                  objc_msgSend(v45, "setObject:forKey:", v34, v32);
                  v46 = v45;
                  v29 = v56;
                  objc_release(v46);
                }
                objc_msgSend(v31, "setEnabled:", 0LL);
              }
            }
            objc_release(v36);
            objc_release(v34);
            objc_release(v32);
            ++v30;
          }
          while ( v30 < (unsigned __int64)v55 );
          v55 = objc_msgSend(v52, "countByEnumeratingWithState:objects:count:", &v57, &v61, 16LL);
        }
        while ( v55 );
      }
      objc_release(v52);
      v9 = v49;
      v8 = v50;
      v12 = v48;
    }
  }
  else
  {
    objc_release(v23);
    objc_release(v22);
  }
  objc_release(v9);
  result = (id)objc_release(v8);
  if ( __stack_chk_guard == v62 )
    result = (id)objc_autoreleaseReturnValue(v12);
  return result;
}
