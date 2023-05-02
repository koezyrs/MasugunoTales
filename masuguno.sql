-- phpMyAdmin SQL Dump
-- version 5.1.1
-- https://www.phpmyadmin.net/
--
-- Máy chủ: 127.0.0.1
-- Thời gian đã tạo: Th4 29, 2023 lúc 08:52 AM
-- Phiên bản máy phục vụ: 10.4.22-MariaDB
-- Phiên bản PHP: 7.4.27

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Cơ sở dữ liệu: `test`
--

-- --------------------------------------------------------

--
-- Cấu trúc bảng cho bảng `accounts`
--

CREATE TABLE `accounts` (
  `id` int(11) NOT NULL,
  `username` varchar(20) NOT NULL,
  `password` varchar(32) NOT NULL,
  `email` varchar(50) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- --------------------------------------------------------

--
-- Cấu trúc bảng cho bảng `actors`
--

CREATE TABLE `actors` (
  `id` int(11) NOT NULL,
  `account_id` int(11) NOT NULL,
  `character_name` varchar(20) NOT NULL,
  `level` int(11) NOT NULL,
  `experience` int(11) NOT NULL,
  `experience_to_next_level` int(11) NOT NULL,
  `strength` int(11) NOT NULL,
  `dexterity` int(11) NOT NULL,
  `intelligence` int(11) NOT NULL,
  `vitality` int(11) NOT NULL,
  `agility` int(11) NOT NULL,
  `stats_used` int(11) NOT NULL,
  `stats_available` int(11) NOT NULL,
  `map_id` int(11) NOT NULL,
  `x` int(11) NOT NULL,
  `y` int(11) NOT NULL,
  `gold` int(11) NOT NULL,
  `skin` varchar(100) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- --------------------------------------------------------

--
-- Cấu trúc bảng cho bảng `actor_character_information`
--

CREATE TABLE `actor_character_information` (
  `id` int(11) NOT NULL,
  `actor_id` int(11) NOT NULL,
  `slot_id` int(11) NOT NULL,
  `equipment_id` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- --------------------------------------------------------

--
-- Cấu trúc bảng cho bảng `actor_inventory`
--

CREATE TABLE `actor_inventory` (
  `id` int(11) NOT NULL,
  `actor_id` int(11) NOT NULL,
  `slot_id` int(11) NOT NULL,
  `equipment_id` int(11) NOT NULL,
  `item_id` int(11) NOT NULL,
  `item_amount` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- --------------------------------------------------------

--
-- Cấu trúc bảng cho bảng `actor_monster_kills`
--

CREATE TABLE `actor_monster_kills` (
  `id` int(11) NOT NULL,
  `actor_id` int(11) NOT NULL,
  `monster_id` int(11) NOT NULL,
  `amount` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- --------------------------------------------------------

--
-- Cấu trúc bảng cho bảng `actor_quest`
--

CREATE TABLE `actor_quest` (
  `id` int(11) NOT NULL,
  `actor_id` int(11) NOT NULL,
  `quest_id` int(11) NOT NULL,
  `progress` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- --------------------------------------------------------

--
-- Cấu trúc bảng cho bảng `actor_ranking`
--

CREATE TABLE `actor_ranking` (
  `id` int(11) NOT NULL,
  `actor_id` int(11) NOT NULL,
  `character_name` varchar(20) NOT NULL,
  `actor_power` int(11) NOT NULL,
  `actor_gold` int(11) NOT NULL,
  `actor_level` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- --------------------------------------------------------

--
-- Cấu trúc bảng cho bảng `actor_variable`
--

CREATE TABLE `actor_variable` (
  `id` int(11) NOT NULL,
  `actor_id` int(11) NOT NULL,
  `variable_id` int(11) NOT NULL,
  `variable_value` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Chỉ mục cho các bảng đã đổ
--

--
-- Chỉ mục cho bảng `accounts`
--
ALTER TABLE `accounts`
  ADD PRIMARY KEY (`id`);

--
-- Chỉ mục cho bảng `actors`
--
ALTER TABLE `actors`
  ADD PRIMARY KEY (`id`);

--
-- Chỉ mục cho bảng `actor_character_information`
--
ALTER TABLE `actor_character_information`
  ADD PRIMARY KEY (`id`);

--
-- Chỉ mục cho bảng `actor_inventory`
--
ALTER TABLE `actor_inventory`
  ADD PRIMARY KEY (`id`);

--
-- Chỉ mục cho bảng `actor_monster_kills`
--
ALTER TABLE `actor_monster_kills`
  ADD PRIMARY KEY (`id`);

--
-- Chỉ mục cho bảng `actor_quest`
--
ALTER TABLE `actor_quest`
  ADD PRIMARY KEY (`id`);

--
-- Chỉ mục cho bảng `actor_ranking`
--
ALTER TABLE `actor_ranking`
  ADD PRIMARY KEY (`id`);

--
-- Chỉ mục cho bảng `actor_variable`
--
ALTER TABLE `actor_variable`
  ADD PRIMARY KEY (`id`);

--
-- AUTO_INCREMENT cho các bảng đã đổ
--

--
-- AUTO_INCREMENT cho bảng `accounts`
--
ALTER TABLE `accounts`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT cho bảng `actors`
--
ALTER TABLE `actors`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT cho bảng `actor_character_information`
--
ALTER TABLE `actor_character_information`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT cho bảng `actor_inventory`
--
ALTER TABLE `actor_inventory`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT cho bảng `actor_monster_kills`
--
ALTER TABLE `actor_monster_kills`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT cho bảng `actor_quest`
--
ALTER TABLE `actor_quest`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT cho bảng `actor_ranking`
--
ALTER TABLE `actor_ranking`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT cho bảng `actor_variable`
--
ALTER TABLE `actor_variable`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
