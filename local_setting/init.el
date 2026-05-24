;; .emacs

;;; uncomment this line to disable loading of "default.el" at startup
;; (setq inhibit-default-init t)

;; enable visual feedback on selections
                                        ;(setq transient-mark-mode t)

;; default to better frame titles
(setq frame-title-format
      (concat  "%b - emacs@" (system-name)))

;; default to unified diffs
(setq diff-switches "-u")

;; always end a file with a newline
                                        ;(setq require-final-newline 'query)

;;; uncomment for CJK utf-8 support for non-Asian users
;; (require 'un-define)

;; Enable Ctrl-z for suspend foreground job
(setq inhibit-default-init t)

;; Display line numbers on the left
(global-linum-mode t)
(setq linum-format "%4d  ")

;; Highlight the current line
(global-hl-line-mode)
(set-face-background 'hl-line "#43494d")
(set-face-foreground 'highlight nil)

(custom-set-variables
 ;; custom-set-variables was added by Custom.
 ;; If you edit it by hand, you could mess it up, so be careful.
 ;; Your init file should contain only one such instance.
 ;; If there is more than one, they won't work right.
 '(inhibit-startup-screen t)
 '(show-paren-mode t)
 '(tool-bar-mode nil))
(custom-set-faces
 ;; custom-set-faces was added by Custom.
 ;; If you edit it by hand, you could mess it up, so be careful.
 ;; Your init file should contain only one such instance.
 ;; If there is more than one, they won't work right.
 '(font-lock-builtin-face ((t (:foreground "yellow" :weight bold))))
 '(font-lock-constant-face ((t (:foreground "green"))))
 '(font-lock-function-name-face ((t (:foreground "magenta" :weight bold))))
 '(font-lock-keyword-face ((t (:foreground "magenta" :weight bold))))
 '(font-lock-preprocessor-face ((t (:inherit font-lock-builtin-face :foreground "yellow"))))
 '(font-lock-string-face ((t (:foreground "cyan")))))
(line-number-mode t)
(column-number-mode t)
(setq make-backup-files nil)
(setq auto-save-default nil)
(setq frame-title-format "%b")
(global-unset-key [insert])
(global-unset-key [insertchar])
(global-set-key (kbd "C-\\") 'other-window)
(global-set-key (kbd "C-/") 'undo)
(global-set-key (kbd "C-?") 'undo)
(global-set-key (kbd "M-;") 'comment-dwim)
(define-key global-map (kbd "C-h") 'delete-backward-char)
(add-hook 'before-save-hook 'delete-trailing-whitespace)

(c-set-offset 'innamespace 0)

;; for python
(add-hook 'python-mode-hook
          '(lambda ()
             (setq python-indent 2)
             (setq indent-tabs-mod nil)
             ))

;; open a buffer list on the current window
(global-set-key "\C-x\C-b" 'buffer-menu)

(global-font-lock-mode t)

;; markdown-mode
(autoload 'markdown-mode "markdown-mode"
  "Major mode for editing Markdown files" t)
(add-to-list 'auto-mode-alist '("\\.md\\'" . markdown-mode))
(setq markdown-fontify-code-blocks-natively t)

;; align-regexp with spaces
(defun align-regexp-with-spaces (orig-fun &rest args)
  (let ((indent-tabs-mode nil)
        (align-to-tab-stop nil))
    (apply orig-fun args)))

(advice-add 'align-regexp :around #'align-regexp-with-spaces)
