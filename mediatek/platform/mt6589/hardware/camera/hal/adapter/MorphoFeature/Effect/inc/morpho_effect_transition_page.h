/**
 * @file    morpho_effect_transition_page.h
 * @brief   Morpho Transition Effect "PAGE" module.
 *
 * effect_name     ...  "TR_PAGE"
 * needs_image_num ...  2
 *
 * Copyright (C) 2009 Morpho, Inc.
 */
#ifndef MORPHO_EFFECT_TRANSTION_PAGE_H
#define MORPHO_EFFECT_TRANSTION_PAGE_H

#ifdef __cplusplus
extern "C" {
#endif

/**  
 * TR_PAGE �G�t�F�N�g�̃p�����[�^.
 * morpho_EffectEngine_setEffectParam() �Őݒ肵�Ă��������B
 */
typedef struct {
    int renders2x2; /**< 2x2�`����s�����ǂ��� */
    int color_r; /**< �w�i�F(r����) */
    int color_g; /**< �w�i�F(g����) */
    int color_b; /**< �w�i�F(b����) */
    const morpho_ImageData* p_bg_image;  /**< �w�i�摜. */
    int draw_all_bg; /**<�w�i�F�A�w�i�摜���o�͉摜�S�̂ɕ`�悷�邩�ǂ��� 0�c�h��Ԃ��Ȃ� 1�c�w��rect�̂� 2�c�o�͉摜�S�� */
    int reverse; /**<�t�Đ����邩�ǂ��� 0..���Ȃ�(���Đ�) 1..���� */
} morpho_EffectTransitionPageParam;

#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif /* #ifndef MORPHO_EFFECT_TRANSTION_PAGE_H */